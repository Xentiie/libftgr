/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfthttp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 02:00:18 by reclaire          #+#    #+#             */
/*   Updated: 2024/08/23 22:18:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfthttp.h"
#include "libft/std.h"
#include "libft/io.h"
#include "libft/socket.h"
#include "libft/strings.h"
#include <stdlib.h>

#include <stdarg.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

const static string methods_str[] = {
	"GET",
	"POST"};

t_http_request *fthttp_new_request()
{
	t_http_request *request = malloc(sizeof(t_http_request));

	ft_bzero(request, sizeof(t_http_request));
	return request;
}

t_http_request *fthttp_make_request(t_http_request *request, enum e_http_method method, string url, U8 *content)
{
	if (request == NULL)
		request = fthttp_new_request();

	request->method = method;
	fthttp_set_url(request, url);
	request->content = content;

	return request;
}

t_http_request *fthttp_make_request_from_template(t_http_request *template)
{
	t_http_request *request = fthttp_new_request();

	request->method = template->method;

	if (request->protocol)
		request->protocol = ft_strdup(template->protocol);
	if (request->domain)
		request->domain = ft_strdup(template->domain);
	if (request->path)
		request->path = ft_strdup(template->path);

	if (template->content != NULL && template->content_size != 0)
	{
		request->content = malloc(sizeof(U8) * template->content_size);
		request->content_size = template->content_size;
		ft_memcpy(request->content, template->content, sizeof(U8) * request->content_size);
	}

	if (request->headers.headers_alloc != 0 && template->headers.headers_count != 0 && template->headers.headers != NULL)
	{
		request->headers.headers_alloc = template->headers.headers_alloc;
		request->headers.headers_count = template->headers.headers_count;
		// TODO
	}
}

void fthttp_set_url(t_http_request *request, string url)
{
	string save;

	save = url;
	while (ft_isalpha(*url))
		url++;
	if (!ft_strncmp(url, "://", 3))
	{
		if (url - save == 0)
			request->protocol = "https";
		else
			request->protocol = ft_strndup(save, url - save);
		url += 3;
	}
	else
	{
		request->protocol = "https";
		url = save;
	}

	save = url;
	while (*url && *url != '/')
		url++;
	if (url - save == 0)
		request->domain = NULL;
	else
		request->domain = ft_strndup(save, url - save);

	if (*url == '\0')
		request->path = ft_strdup("/");
	else
		request->path = ft_strdup(url);
}

void fthttp_resolve_url_params(t_http_request *request, ...)
{
	va_list list;
	va_list save;

	va_start(list, request);
	va_copy(save, list);

	string p = va_arg(list, string);
	U64 len = 0;
	while (p)
	{
		len += ft_strlen(p);
		p = va_arg(list, string);
	}
	va_end(list);

	string path = request->path;
	len += ft_strlen(path);
	request->path = malloc(sizeof(char) * (len + 1));
	ft_memset(request->path, 0, sizeof(char) * (len + 1));

	// vsnprintf(request->path, sizeof(char) * (len + 1), path, cpy);
	ft_vsnprintf(request->path, sizeof(char) * (len + 1), path, save);
	va_end(save);

	free(path);
}

void fthttp_url_encode(t_http_request *request)
{
#define IS_RESERVED_CHAR(x) (!(ft_isalnum(x) || (x == '-' || x == '.' || x == '_' || x == '~' || x == '/')))
	U64 len = 0;
	for (U64 i = 0; request->path[i]; i++)
	{
		if (IS_RESERVED_CHAR(request->path[i]))
			len += 3;
		else
			len++;
	}

	string url_encoded = malloc(sizeof(U8) * (len + 1));
	ft_memset(url_encoded, 0, sizeof(U8) * (len + 1));
	for (U64 i = 0, j = 0; request->path[i]; i++)
	{
		if (IS_RESERVED_CHAR(request->path[i]))
			j += ft_snprintf(&url_encoded[j], len - j, "%%%X", request->path[i]);
		else
			url_encoded[j++] = request->path[i];
	}

	free(request->path);
	request->path = url_encoded;
}

enum e_http_request_stream_state
{
	FIRST_LINE,
	HEADERS,
	CONTENT,
};

typedef struct s_http_request_parser
{
	enum e_http_request_stream_state state;
	string buffer;
	U64 len;
	U64 alloc;
}	t_http_request_parser;

S32 fthttp_response_parse(string data, U64 data_size, t_http_request_parser *parser, t_http_response *response)
{
	U64 l;
	U64 tmp;

/*
s'occuper de tout ce qu'il y a dans data, et sauvegarder le reste
*/

	if (parser->buffer == NULL)
	{
		parser->buffer = malloc(sizeof(U8) * 256);
		parser->alloc = 256;
	}

	switch (parser->state)
	{
	case FIRST_LINE:;
		string eol = ft_strnstr(data, "\r\n", data_size);
		if (!eol)
			goto cpy_remaining;

		tmp = (U64)ft_strnchr(data, ' ', eol - data);
		if (tmp == 0)
			goto quit_error;
		

		break;
	case HEADERS:
		break;
	case CONTENT:
		break;
	}

cpy_remaining:
	if (parser->len + data_size > parser->alloc)
	{
		string new_buffer = malloc(sizeof(U8) * parser->alloc * 2);
		ft_memcpy(new_buffer, parser->buffer, parser->len);
		free(parser->buffer);
		parser->buffer = new_buffer;
		parser->alloc *= 2;
	}
	ft_memcpy(parser->buffer + parser->len, data, data_size);

quit_continue:
	return 1;
quit_done:
	return 0;
quit_error:
	return -1;
}


#define FTHTTP_EHOSTNAME 1
#define FTHTTP_ESOCK 2
#define FTHTTP_ECONNECT 3
#define FTHTTP_ESEND 4
#define FTHTTP_ERECV 5
S32 fthttp_request_send(t_http_request *request, t_http_response *response)
{
	struct addrinfo addr;

	string port; // 80 (http) or 443 (https)
	file socket;

	U64 request_headers_len;
	string headers, ptr;

	S64 ret;		 // return value from send / recv
	S64 sent, received;

	if (ft_resolve_hostname(&addr, request->domain, "80") != 0)
		return FTHTTP_EHOSTNAME;

	if ((socket = ft_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == (file)-1)
		return FTHTTP_ESOCK;

	if (ft_connect(socket, (const struct sockaddr *)addr.ai_addr, addr.ai_addrlen) != 0)
		return FTHTTP_ECONNECT;

	{
		request_headers_len = (ft_strlen(methods_str[request->method]) + 1 /* space */ +
							   ft_strlen(request->path) + 1 /* space */ + 19 /* HTTP/1.0... */ + 2 /* \r\n */ +
							   ft_strlen(request->domain) + 2 /* \r\n */ +
							   /* \r\n */ 2 +
							   /* \0 */ 1);
		for (S32 i = 0; i < request->headers.headers_count; i++)
		{
			request_headers_len += ft_strlen(request->headers.headers[i * 2]);
			request_headers_len += 2;
			request_headers_len += ft_strlen(request->headers.headers[i * 2 + 1]);
			request_headers_len += 2;
		}
	}

	headers = malloc(sizeof(char) * request_headers_len);
	headers[0] = '\0';

	ptr = headers;
	ptr += ft_snprintf(ptr, request_headers_len, "%s %s HTTP/1.0\r\n", methods_str[request->method], request->path);
	ptr += ft_snprintf(ptr, request_headers_len - (ptr - headers), "Host: %s\r\n", request->domain);

	for (S32 i = 0; i < request->headers.headers_count; i++)
		ptr += ft_snprintf(ptr, request_headers_len - (ptr - headers), "%s: %s\r\n", request->headers.headers[i * 2], request->headers.headers[i * 2 + 1]);
	*ptr++ = '\r';
	*ptr++ = '\n';
	*ptr = '\0';

	{
		sent = 0;
		while ((ret = ft_send(socket, headers + sent, request_headers_len - sent, 0)) > 0)
			sent += ret;
		if (ret == -1)
			return FTHTTP_ESEND;

		if (request->content != 0 && request->content_size > 0)
		{
			sent = 0;
			while ((ret = ft_send(socket, request->content + sent, request->content_size - sent, 0)))
				sent += ret;
			if (ret == -1)
				return FTHTTP_ESEND;
		}
	}

	char buf[4096];
	ptr = buf;
	received = 0;
	U64 tmp;
	ft_memset(response, 0, sizeof(t_http_response));
	while ((ret = ft_recv(socket, buf + received, sizeof(buf) - received, 0)) > 0)
	{
		received += ret;
		if (!ft_strnstr(buf, "\r\n\r\n", received))
			continue;
		
		
	}
}

void fthttp_add_header(t_http_headers *headers, string key, string value)
{
	if (headers->headers_alloc >= headers->headers_count)
	{
		string *new = malloc(sizeof(string *) * headers->headers_alloc * 2);
		ft_memcpy(new, headers->headers, sizeof(string *) * headers->headers_count);
		free(headers->headers);
		headers->headers_alloc *= 2;
		headers->headers = new;
	}

	headers->headers[headers->headers_count * 2] = ft_strdup(key);
	headers->headers[headers->headers_count * 2 + 1] = ft_strdup(value);
	headers->headers_count++;
}

void fthttp_request_print(t_http_request *request)
{
	printf("Request %#016x: {\n\tmethod: %s\n\turl:%s://%s%s\n\tcontent: %.20s%s (%lu)\n}\n", request,
		   methods_str[request->method],
		   request->protocol, request->domain, request->path,
		   request->content, (request->content_size > 20 ? "..." : ""), request->content_size);
}

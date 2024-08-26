/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 03:12:47 by reclaire          #+#    #+#             */
/*   Updated: 2024/08/23 22:17:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "centrale.h"
#include "libft/io.h"
#include "libft/lists.h"
#include "libfthttp.h"
#include "libft/socket.h"
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in *)sa)->sin_addr);
	return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

LPCSTR inet_ntop(INT Family, LPCVOID pAddr, LPSTR pStringBuf, size_t StringBufSize);
int main2(int argc, char **argv)
{
	t_http_request *request = fthttp_new_request();
	request->method = GET;
	fthttp_set_url(request, "http://api.brawlstars.com/v1/players/%s/battlelog");
	//fthttp_set_url(request, "google.com/%s");
	fthttp_resolve_url_params(request, argv[1], NULL);
	fthttp_url_encode(request);

	fthttp_request_print(request);

	t_http_response response;
	fthttp_request_send(request, &response);
	return 0;

	S32 ret;
	string port = argc >= 3 ? port = argv[2] : NULL;

	struct addrinfo addr;
	if (ft_resolve_hostname(&addr, argv[1], port) != 0)
	{
		ft_dprintf(ft_stderr, "couldn't resolve hostname\n");
		return 1;
	}

	char s[INET6_ADDRSTRLEN];
	inet_ntop(addr.ai_family, get_in_addr((struct sockaddr *)addr.ai_addr), s, sizeof s);
	if (port)
		ft_printf("ADDRESSE: %s:%s\n", argv[1], port);
	else
		ft_printf("ADDRESSE: %s\n", argv[1]);
	ft_printf("IP: %s\n", s);

	file sock = ft_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == (file)-1)
	{
		ft_dprintf(ft_stderr, "couldn't open socket\n");
		return 1;
	}

	if ((ret = connect((SOCKET)sock, addr.ai_addr, addr.ai_addrlen)) != 0)
	{
		ft_dprintf(ft_stderr, "couldn't connect: %d\n", ret);
		return 1;
	}

	char http_request[200];

	U64 length = ft_snprintf(http_request, sizeof(http_request), "GET / HTTP/1.1\r\nHost: %s/imghp?hl=en&authuser=0&ogbl\r\n\r\n", argv[1]);

	//printf("Sent: %d\n", ft_fwrite(sock, http_request, length));

	//send(sock, http_request, length, 0);
	ft_send(sock, http_request, length, 0);


	char buf[256];
	length = ft_recv(sock, buf, sizeof(buf), 0);
	printf("|%.*s| (%d)\n", length, buf, length);
}

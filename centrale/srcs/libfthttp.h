/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfthttp.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 02:00:26 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/11 01:17:04 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTHTTP_H
#define LIBFTHTTP_H

#include "libft/std.h"

enum e_http_method
{
	GET,
	POST
};

typedef struct s_http_headers
{
	//List of tuples: key value
	string *headers;
	U32 headers_count;
	U32 headers_alloc;
}	t_http_headers;

typedef struct s_http_request
{
	enum e_http_method method;
	string protocol;
	string domain;
	string path;
	t_http_headers headers;
	U8 *content;
	U64 content_size;
}	t_http_request;

typedef struct s_http_response
{
	U16 http_ver; //fixed float (8 bits each)
	S32 code;
	t_http_headers headers;
	U8 *content;
}	t_http_response;

t_http_request *fthttp_new_request();

/*
request can be NULL, then it will be allocated
if method == GET, content will be ignored.
if content is NULL, it will be considered as an empty string ( "" )
url will be parsed using fthttp_set_url
*/
t_http_request *fthttp_make_request(t_http_request *request, enum e_http_method method, string url, U8 *content);
void fthttp_set_url(t_http_request *request, string url);
void fthttp_resolve_url_params(t_http_request *request, ...);
void fthttp_url_encode(t_http_request *request);
void fthttp_add_header(t_http_headers *headers, string key, string value);

S32 fthttp_request_send(t_http_request *request, t_http_response *response);
void fthttp_request_print(t_http_request *request);


#endif
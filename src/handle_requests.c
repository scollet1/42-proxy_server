/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_requests.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:57:23 by cyildiri          #+#    #+#             */
/*   Updated: 2017/05/07 21:12:04 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proxy.h"

void	handle_requests(int server_sock, int buff_size,
		struct sockaddr_in *addr, size_t *addrlen)
{
	char	*buffer;
	int		bytes_read;
	int		client_sock;
	char	*response;

	client_sock = 0;
	buffer = (char *)malloc(buff_size);
	while (1)
	{
		if ((bytes_read = recv(client_sock, buffer, buff_size, 0)) > 0)
		{
			printf("recieved request:\n%s\n", buffer);
			bzero(buffer, buff_size);
			response = web_request("GET /index.html HTTP/1.1\r\n"
			"Host: www.qst0.com\r\n\r\n");
			send(client_sock, response, strlen(response), 0);
		}
		else
			client_sock = accept(server_sock, (struct sockaddr *)addr,
							(socklen_t *)addrlen);
	}
}

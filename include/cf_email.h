#ifndef CF_EMAIL_H
#define CF_EMAIL_H
#include "cf_string.h"
#include "cf_socket.h"
typedef struct  cf_smtp_account
{
	struct cf_sockaddr sock_addr;
	CFString* login_name;
	CFString* login_password;
} CFSmtpAccount;
CFSmtpAccount* cf_smtp_account_new(struct sockaddr addr, int addr_len, 
									const char* login_name, const char* login_password);
int cf_smtp_account_free();

typedef int(*cf_email_gen_attachement_func)(void* data, int email_con_fd);
int smtp_send(CFString* rcpt_to, CFString* mail_from, CFSmtpAccount* smtpAcount,
				CFString* content, cf_email_gen_attachment_func gen_attachment_fun, void* data);

#endif

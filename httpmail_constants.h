/*
 *  httpmail_constants.h
 *  httpmail
 *
 *  Created by Daniel Parnell on Mon Sep 30 2002.
 *  Copyright (c) 2002 Daniel Parnell. All rights reserved.
 *
 */

#define HTTPMAIL_URL @"http://services.msn.com/svcs/hotmail/httpmail.asp"
#define HTTPMAIL_MSN_URL @"http://oe.msn.msnmail.hotmail.com/cgi-bin/hmdata"

#define HTTPMAIL_FIND_FOLDERS @"<?xml version=\"1.0\"?>\r\n\
<D:propfind xmlns:D=\"DAV:\" xmlns:h=\"http://schemas.microsoft.com/hotmail/\" xmlns:hm=\"urn:schemas:httpmail:\">\r\n\
\t<D:prop>\r\n\
\t\t<h:adbar/>\r\n\
\t\t<hm:contacts/>\r\n\
\t\t<hm:inbox/>\r\n\
\t\t<hm:outbox/>\r\n\
\t\t<hm:sendmsg/>\r\n\
\t\t<hm:sentitems/>\r\n\
\t\t<hm:deleteditems/>\r\n\
\t\t<hm:drafts/>\r\n\
\t\t<hm:msgfolderroot/>\r\n\
\t\t<h:maxpoll/>\r\n\
\t\t<h:modified/>\r\n\
\t\t<h:sig/>\r\n\
\t</D:prop>\r\n\
</D:propfind>\r\n\r\n"

#define HTTPMAIL_FIND_SUBFOLDERS @"<?xml version=\"1.0\"?>\n\
<D:propfind xmlns:D=\"DAV:\" xmlns:hm=\"urn:schemas:httpmail:\">\n\
        <D:prop>\n\
                <D:isfolder/>\n\
                <D:displayname/>\n\
                <hm:special/>\n\
                <D:hassubs/>\n\
                <D:nosubs/>\n\
                <hm:unreadcount/>\n\
                <D:visiblecount/>\n\
        </D:prop>\n\
</D:propfind>\n"

#define HTTPMAIL_FIND_MESSAGES @"<?xml version=\"1.0\"?>\n\
<D:propfind xmlns:D=\"DAV:\" xmlns:hm=\"urn:schemas:httpmail:\" xmlns:m=\"urn:schemas:mailheader:\">\n\
        <D:prop>\n\
                <D:isfolder/>\n\
                <hm:read/>\n\
                <m:hasattachment/>\n\
                <m:to/>\n\
                <m:from/>\n\
                <m:subject/>\n\
                <m:date/>\n\
                <D:getcontentlength/>\n\
        </D:prop>\n\
</D:propfind>\n"

/*
#define HTTPMAIL_FIND_MESSAGES @"<?xml version=\"1.0\"?>\n\
<D:propfind xmlns:D=\"DAV:\" xmlns:hm=\"urn:schemas:httpmail:\" xmlns:m=\"urn:schemas:mailheader:\">\n\
    <allprop/>\n\
</D:propfind>\n"
*/

/*
From: Marc <tmx49@hotmail.com>
Date: Tue Apr 22, 2003  10:33:14 AM Australia/Canberra
To: danielparnell@hotmail.com
Subject: error while checking
Message-Id: <20030422003516.3ea48e4424467@hotmail.com>
Message-Id: <01641D8D-745A-11D7-ABF2-000393AD5B80@hotmail.com>
Received: from 80.58.33.235 by oe40.law12.hotmail.com with DAV; Tue, 22 Apr 2003 00:35:16 +0000
X-Originating-Ip: [80.58.33.235]
X-Originating-Email: [tmx49@hotmail.com]
Mime-Version: 1.0 (Apple Message framework v552)
Content-Type: text/plain; charset=US-ASCII; format=flowed
Content-Transfer-Encoding: 7bit
X-Mailer: Apple Mail (2.552)
Httpmailuid: MSG1050971716.9
Httpmailfolder: inbox
*/

#define HTTPMAIL_MARK_READ @"<?xml version=\"1.0\"?>\n\
<D:propertyupdate xmlns:D=\"DAV:\" xmlns:hm=\"urn:schemas:httpmail:\">\n\
        <D:set>\n\
                <D:prop>\n\
                        <hm:read>1</hm:read>\n\
                </D:prop>\n\
        </D:set>\n\
</D:propertyupdate>\n"

#define HTTPMAIL_MARK_UNREAD @"<?xml version=\"1.0\"?>\n\
<D:propertyupdate xmlns:D=\"DAV:\" xmlns:hm=\"urn:schemas:httpmail:\">\n\
        <D:set>\n\
                <D:prop>\n\
                        <hm:read>0</hm:read>\n\
                </D:prop>\n\
        </D:set>\n\
</D:propertyupdate>\n"

#define HTTPMAIL_MOVE_MAIL @"<?xml version=\"1.0\"?>\r\n\
<D:move xmlns:D=\"DAV:\">\r\n\
\t<D:target>\r\n\
%@\r\n\
\t</D:target>\r\n\
</D:move>\r\n"

#define HTTPMAIL_RECIPIENT @"RCPT TO:<%@>\r\n"
#define HTTPMAIL_SEND_MESSAGE @"MAIL FROM:<%@>\r\n%@\r\n%@\r\n"

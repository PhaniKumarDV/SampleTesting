#ifndef _REGX_H
#define _REGX_H

#ifdef __cplusplus
extern "C" {
#endif

int regxMatch(const char *pattern, const char *subject);

// we define some useful pattens in order to guarantee the validity of object
// reference: http://regexlib.com/Search.aspx
/**********************careful******************************************
be careful for these four special letters: '  "  \  /
you have to them change to \' \" \\ \/
***********************************************************************/

#define MAC_REGX            "^([0-9a-fA-F][0-9a-fA-F]:){5}([0-9a-fA-F][0-9a-fA-F])$"
/*************************************************************************************************

Expression:     
^([0-9a-fA-F][0-9a-fA-F]:){5}([0-9a-fA-F][0-9a-fA-F])$
 
Description:    This will grep for a valid MAC address , with colons seperating octets. It will ignore strings too short or long, or with invalid characters. It will accept mixed case hexadecimal. Use extended grep.
Matches:    01:23:45:67:89:ab|||01:23:45:67:89:AB|||fE:dC:bA:98:76:54
Non-Matches:    01:23:45:67:89:ab:cd|||01:23:45:67:89:Az|||01:23:45:56:
 
Author:     Ted Rudyk
**************************************************************************************************/
#define HOST_NAME3_REGX      "^([a-zA-Z0-9]([a-zA-Z0-9\\-]{0,10}[a-zA-Z0-9])?[\\.]?){1,3}[a-zA-Z0-9]{2,6}$"
#define HOST_NAME1_REGX      "^([a-zA-Z0-9]([a-zA-Z0-9\\-]{0,61}[a-zA-Z0-9])?\\.)+[a-zA-Z]{2,6}$"
/*************************************************************************************************
Expression:     
^([a-zA-Z0-9]([a-zA-Z0-9\-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,6}$
 
Description:    Checks domain names. This validates domains based on latest specifications (RFCs 952 and 1123 dealing with hostnames and RFC 1035 dealing with domain name system requirements) except that it only includes realistic fully-qualified domains: 1. requires at least one subdomain 2. allows shortest top-level domains like "ca", and "museum" as longest. Other validation rules: 1. Labels/parts should be seperated by period. 2. Each label/part has maximum of 63 characters. 3. First and last character of label must be alphanumeric, other characters alphanumeric or hyphen. 4. Does not check maxlength of domain which incidentally is 253 characters of text (255 binary representation). For a regular expression that matches ALL domains: ^([a-zA-Z0-9]([a-zA-Z0-9\-]{0,61}[a-zA-Z0-9])?\.)*[a-zA-Z0-9]([a-zA-Z0-9\-]{0,61}[a-zA-Z0-9])?$
Matches:    regexlib.com|||this.is.a.museum|||3com.com
Non-Matches:    notadomain-.com|||helloworld.c|||.oops.org
 
Author:     Remi Sabourin
*****************************************************************************************************/

#define HOST_NAME2_REGX      "^[a-zA-Z0-9\\-\\.]+\\.(com|org|net|mil|edu|COM|ORG|NET|MIL|EDU)$" 
/*************************************************************************************************
Expression:     
^[a-zA-Z0-9\-\.]+\.(com|org|net|mil|edu|COM|ORG|NET|MIL|EDU)$
 
Description:    Domain names: This regular expression tests the validity of a domain or hostname. It will match any valid domain name that does not contain characters which are invalid in URLs, and which ends in .com, .org, .net, .mil, or .edu. You can add additional valid TLDs by appending the | (pipe) character and the desired TLD to the list in the parens.
Matches:    3SquareBand.com|||asp.net|||army.mil
Non-Matches:    $SquareBand.com|||asp/dot.net|||army.military
 
Author:     G. Andrew Duthie
**************************************************************************************************/

//Hostname_1 can use in any TLD but Hostname_2 can only use in specific TLD, we also can add other specific TLDs in hostname_2 

#define IP_REGX         "^(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])$"
/**************************************************************************************************
Expression:     
^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$
 
Description:    This matches an IP address, putting each number in its own group that can be retrieved by number. If you do not care about capturing the numbers, then you can make this shorter by putting everything after ^ until immediately after the first \. in a group ( ) with a {3} after it. Then put the number matching regex in once more. It only permits numbers in the range 0-255.
Matches:    0.0.0.0|||255.255.255.02|||192.168.0.136
Non-Matches:    256.1.3.4|||023.44.33.22|||10.57.98.23.
 
Author:     Andrew Polshaw
****************************************************************************************************/

#define IP_REGX_2   "^(25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]{1}\\d{1}|[1-9])\\.(25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]{1}\\d{1}|\\d)\\.(25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]{1}\\d{1}|\\d)\\.(25[0-4]|2[0-4]\\d|1\\d{2}|[1-9]{1}\\d{1}|[1-9])$"
/**************************************************************************************************
Description:    This matches an IP address , and the range is from 1.0.0.1~255.255.255.254
****************************************************************************************************/

#define MULTICAST_IP_REGX "^(22[4-9]|2[3-4][0-9]|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])$"
//^(22[4-9]|2[3-4][0-9]|25[0-5])$
/**************************************************************************************************
Description:    This matches an IP address , and the range is from 224.0.0.0~255.255.255.255
****************************************************************************************************/

/*
#define EMAIL_REGX  "^(?:(?:[^@,\"\\[\\]\\x5c\\x00-\\x20\\x7f-\\xff\\.]|\\x5c(?=[@,\"\\[\\]\\x5c\\x00-\\x20\\x7f-\\xff]))(?:[^@,\"\\[\\]\\x5c\\x00-\\x20\\x7f-\\xff\\.]|(?<=\\x5c)[@,\"\\[\\]\\x5c\\x00-\\x20\\x7f-\\xff]|\\x5c(?=[@,\"\\[\\]\\x5c\\x00-\\x20\\x7f-\\xff])|\\.(?=[^\\.])){1,62}(?:[^@,\"\\[\\]\\x5c\\x00-\\x20\\x7f-\\xff\\.]|(?<=\\x5c)[@,\"\\[\\]\\x5c\\x00-\\x20\\x7f-\\xff])|\"(?:[^\"]|(?<=\\x5c)\"){1,62}\")@(?:(?:[a-z0-9][a-z0-9-]{1,61}[a-z0-9]\\.?)+\\.[a-z]{2,6}|\\[(?:[0-1]?\\d?\\d|2[0-4]\\d|25[0-5])(?:\\.(?:[0-1]?\\d?\\d|2[0-4]\\d|25[0-5])){3}\\])$"
*/
#define EMAIL_REGX "^[A-Za-z0-9](([_\\.\\-]?[a-zA-Z0-9]+)*)@([A-Za-z0-9]+)(([\\.\\-]?[a-zA-Z0-9]+)*)\\.([A-Za-z]{2,})$"
/***************************************************************************************************
Title:      Pattern Title    [Details] [Test]
Expression:     
^(?:(?:[^@,"\[\]\x5c\x00-\x20\x7f-\xff\.]|\x5c(?=[@,"\[\]\x5c\x00-\x20\x7f-\xff]))(?:[^@,"\[\]\x5c\x00-\x20\x7f-\xff\.]|(?<=\x5c)[@,"\[\]\x5c\x00-\x20\x7f-\xff]|\x5c(?=[@,"\[\]\x5c\x00-\x20\x7f-\xff])|\.(?=[^\.])){1,62}(?:[^@,"\[\]\x5c\x00-\x20\x7f-\xff\.]|(?<=\x5c)[@,"\[\]\x5c\x00-\x20\x7f-\xff])|"(?:[^"]|(?<=\x5c)"){1,62}")@(?:(?:[a-z0-9][a-z0-9-]{1,61}[a-z0-9]\.?)+\.[a-z]{2,6}|\[(?:[0-1]?\d?\d|2[0-4]\d|25[0-5])(?:\.(?:[0-1]?\d?\d|2[0-4]\d|25[0-5])){3}\])$
 
Description:    just another email validation perl regexp. I tryed to follow as much as possible the RFC 3696 don't hesitate to report.
Matches:    !def!xyz'abc@ex-ample.com|||Fred\ Bloggs@example.com|||"test"@tsse.com
Non-Matches:    te..st@ex-ample.com|||test@example-.com ||| .test@ex-am_ple.com
 
Author:     jonathan gotti
******************************************************************************************************/

#define PORT_REGX   "^(6553[0-5]|655[0-2]\\d|65[0-4]\\d\\d|6[0-4]\\d{3}|[1-5]\\d{4}|[1-9]\\d{0,3})$"
/***************************************************************************************************
Title:        Port Numbers       [Details] [Test]
Expression:     ^(6553[0-5]|655[0-2]\d|65[0-4]\d\d|6[0-4]\d{3}|[1-5]\d{4}|[1-9]\d{0,3})$
 
Description:    Port Numbers: Well Known Ports, Registered Ports & Dynamic and/or Private Ports: 1 through 65536. Matches numbers in range of 0 through 65536.
Matches:    1023|||49151|||65535
Non-Matches:    65536|||66000|||67000|||0
 
Author:     Dean Dal Bozzo 
******************************************************************************************************/


#define EXTNUMBER_PATTERN_REGX "^\\d{%d}$"
/***************************************************************************************************
Description: This matchs digital numbers,you can define the length
if %d=3
Matches:111,234,987,001,
Non-Matches:01a,a123,113a,aaa
******************************************************************************************************/

#define DIALPLAN_NUMBER_PATTERN_REGX "^\\d{%d,%d}$"
#define FORWARD_NUMBER_PATTERN_REGX "^\\d{%d,%d}$"
/***************************************************************************************************
Description: This matchs digital numbers,you can define the length
if %d=3
Matches:111,234,987,001,
Non-Matches:01a,a123,113a,aaa
******************************************************************************************************/

#define USERNAME_PATTERN_REGX "^[a-zA-Z0-9]\\w{0,%d}$"
/***************************************************************************************************
Description: This matchs A-Z,a-z,0-9,and underlind "_",buf the first character shuld be a alphanumeric letter. you can define the Max length
if w{0,5} no more than 5 characters
Matches:1,a234,a_9Ab,AC3,
Non-Matches:_01aa,a adf,a#45,@#$^
******************************************************************************************************/

#define USERPASSWD_PATTERN_REGX "^[^=\\s]{%d,%d}$"
/***************************************************************************************************
Description: This matchs any characher except "\t \n \r \f" and "=". you can define the Max and min length
if ]{3,5} at lease 3 characters and no more than 5 characters
Matches:@#$,$fa,156d_
Non-Matches:=a,\ta aa,a@#$%^
******************************************************************************************************/

#define USERDESCRIPTION_PATTERN_REGX "^[^=]{0,%d}$"
//#define USERDESCRIPTION_PATTERN_REGX "^[\\w\\s]{0,%d}$"
/***************************************************************************************************
Description: This matchs any characher except "\t \n \r \f",you can define the Max length
if ]{0,5} no more than 5 characters
Matches:@#$,$fa,156d_
Non-Matches:=adf=a,\ta,\ra
******************************************************************************************************/

#define SIP_USER_NAME_REGX "^[\\w%-.!~*()&=+$,;?/]{1,20}$"
/***************************************************************************************************
Description: RFC3261 page.222 :: unreserved /escaped / user-unreserved 
Matches:
Non-Matches:
******************************************************************************************************/

#define SIP_AUTH_NAME_REGX "^[\\w%-.!~*()$,;:@&=+]{0,20}$"
/***************************************************************************************************
Description: RFC3261 page.222 ::  unreserved /escaped / $,;:@&=+ 
Matches:
Non-Matches:
******************************************************************************************************/

#define SIP_AUTH_PASSWORD_REGX "^[\\w%-.!~*()&=+$,]{0,20}$"
/***************************************************************************************************
Description: RFC3261 page.222 ::  unreserved /escaped / &=+$,
Matches:
Non-Matches:
******************************************************************************************************/

#define SIP_URI_REGX "^([\\w%-.!~*'()&=+$,;?/]{1,32}@)?(?:((25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]{1}\\d{1}|[1-9])\\.(25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]{1}\\d{1}|\\d)\\.(25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]{1}\\d{1}|\\d)\\.(25[0-4]|2[0-4]\\d|1\\d{2}|[1-9]{1}\\d{1}|[1-9]))|(([a-zA-Z0-9]([a-zA-Z0-9\\-]{0,61}[a-zA-Z0-9])?\\.)+[a-zA-Z]{2,6}))$"
/***************************************************************************************************
Description: SIP_USER_NAME_REGX @ HOST_NAME1_REGX or SIP_USER_NAME_REGX @ IP_REGX_2
Matches:
Non-Matches:
******************************************************************************************************/

#define SIP_TO_URI_STR_REGX "^To: <sip:([\\w%-.!~*'()&=+$,;?/]{1,32}@)?(?:((25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]{1}\\d{1}|[1-9])\\.(25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]{1}\\d{1}|\\d)\\.(25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]{1}\\d{1}|\\d)\\.(25[0-4]|2[0-4]\\d|1\\d{2}|[1-9]{1}\\d{1}|[1-9]))|(([a-zA-Z0-9]([a-zA-Z0-9\\-]{0,61}[a-zA-Z0-9])?\\.)+[a-zA-Z]{2,6})):(6553[0-5]|655[0-2]\\d|65[0-4]\\d\\d|6[0-4]\\d{3}|[1-5]\\d{4}|[1-9]\\d{0,3})>$"
/***************************************************************************************************
Description: To:<sip:SIP_URI_REGX:PORT_REGX:PORT_REGX>
Matches:
Non-Matches:
******************************************************************************************************/

#define SIP_PROFILE_NAME_REGX "^[^@'\"]{1,12}$"
/***************************************************************************************************
Description: not use @'", can use utf8
Matches:
Non-Matches:
******************************************************************************************************/

#define PHONE_BOOK_NAME_REGX "^[^@'\"]{1,20}$"
/***************************************************************************************************
Description: not use @'", can use utf8
Matches:
Non-Matches:
******************************************************************************************************/

#define PHONE_BOOK_TEL_REGX "^([+]\\d{0,29}|\\d{0,30})$"
/***************************************************************************************************
Description: accept number and first bit is "+"
Matches:
Non-Matches:
******************************************************************************************************/

#define MAKE_CALL_URL_REGX	"^([A-Za-z0-9](([_\\.\\-]?[a-zA-Z0-9]+)*)@)?(?:(?:\\[?(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?))\\.){3}(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\]?)|(?:[a-zA-Z0-9-]+\\.)+(?:[a-zA-Z]){2,}\\.?)(:(6553[0-5]|655[0-2]\\d|65[0-4]\\d\\d|6[0-4]\\d{3}|[1-5]\\d{4}|[1-9]\\d{0,3}))?$"
#define MAKE_CALL_NAME_REGX	"^[A-Za-z0-9](([_\\.\\-]?[a-zA-Z0-9]+)*)$"
/***************************************************************************************************
Description: phone book URL , forward Number, new message URL
Matches:
Non-Matches:
******************************************************************************************************/

#define SIP_TOS_DIFFSERV_REGX "^[0-9a-fA-F][0-9a-fA-F]$"
/***************************************************************************************************
Description: Tos/Diffserv
Matches: 00 ~ FF
Non-Matches:
******************************************************************************************************/

#define IPV6_REGX   "^((([0-9A-Fa-f]{1,4}:){7}([0-9A-Fa-f]{1,4}|:))|(([0-9A-Fa-f]{1,4}:){6}(:[0-9A-Fa-f]{1,4}|((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3})|:))|(([0-9A-Fa-f]{1,4}:){5}(((:[0-9A-Fa-f]{1,4}){1,2})|:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3})|:))|(([0-9A-Fa-f]{1,4}:){4}(((:[0-9A-Fa-f]{1,4}){1,3})|((:[0-9A-Fa-f]{1,4})?:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(([0-9A-Fa-f]{1,4}:){3}(((:[0-9A-Fa-f]{1,4}){1,4})|((:[0-9A-Fa-f]{1,4}){0,2}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(([0-9A-Fa-f]{1,4}:){2}(((:[0-9A-Fa-f]{1,4}){1,5})|((:[0-9A-Fa-f]{1,4}){0,3}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(([0-9A-Fa-f]{1,4}:){1}(((:[0-9A-Fa-f]{1,4}){1,6})|((:[0-9A-Fa-f]{1,4}){0,4}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(:(((:[0-9A-Fa-f]{1,4}){1,7})|((:[0-9A-Fa-f]{1,4}){0,5}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:)))(%.+)?$"
/***************************************************************************************************
Description:    A Regular Expression for IPv6 Addresses
Matches:    
fe80:0000:0000:0000:0204:61ff:fe9d:f156 // full form of IPv6
fe80:0:0:0:204:61ff:fe9d:f156 // drop leading zeroes
fe80::204:61ff:fe9d:f156 // collapse multiple zeroes to :: in the IPv6 address
fe80:0000:0000:0000:0204:61ff:254.157.241.86 // IPv4 dotted quad at the end
fe80:0:0:0:0204:61ff:254.157.241.86 // drop leading zeroes, IPv4 dotted quad at the end
fe80::204:61ff:254.157.241.86 // dotted quad at the end, multiple zeroes collapsed
::1 // localhost
fe80:: // link-local prefix
2001:: // global unicast prefix 
Non-Matches:    
 
Author:     Rich Brown 
******************************************************************************************************/


#ifdef __cplusplus
}
#endif

#endif /* _REGX_H */

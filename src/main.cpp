/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/* <DESC>
 * simple HTTP POST using the easy interface
 * </DESC>
 */

//#include <ctype.h>
#include <stdio.h> // strncmp()
#include <string.h>
//#include <iostream>

#include <getopt.h> 
#include <string>
#include <stdlib.h>

#include <curl/curl.h>

#define DEFAULT_MANUFACTURER "Optoma"
#define DEFAULT_MODELLNAME "ZU660e"
#define DEFAULT_PROTOCOL "http://"
#define DEFAULT_IP "192.168.0.255"
#define DEFAULT_MODE "set"

#define BASE_PAGE "/act.cgi?"

int main (int argc, char **argv)
{
  //char *ip_addres = NULL;
  const char *mode = DEFAULT_MODE;

  ///"http://192.168.0.100/act.cgi?c=set&t=main&1=1"
  
  /**********************************
  * page main (t=main):
  * 
  * 1: powerOn/Off (1/0)
  * 2:  ...
  * .
  * .
  * .
  * 13: ...
  **********************************/
  std::string protocol = DEFAULT_PROTOCOL;
  std::string ip_addres = DEFAULT_IP;
  std::string base_page = BASE_PAGE;
  std::string command = "c=";             /// set,get,...more?
  std::string page = "t=";                /// 
  std::string uri;                      /// = protocol + ip_addres + base_page;

  int index;
  int c;

  opterr = 0;

  while ((c = getopt (argc, argv, "t:bc:m:")) != -1)
    switch (c) {
      case 't':
        page += optarg;
        break;
      case 'c':
        ip_addres = optarg;
        break;
      case 'm':
        if ( strcmp(optarg, "get") )
          mode = optarg;
        else
          fprintf (stderr, "optarg = %s \n", optarg);
          mode = optarg;
        break;        
      case '?':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }
      uri += ip_addres;
      uri += "/act.cgi?c=";
      uri += mode;
      uri += "&t=main&";
      uri += "1=1";

    printf ("ip_addres = %s\n, mode = %s\n, uri = %s\n,",
          ip_addres.c_str(), mode, uri.c_str());

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
  
  CURL *curl;
  CURLcode res;

  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  struct curl_slist *list = NULL;

  if(curl) {
//    curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.0.100/act.cgi?c=set&t=main&1=1");
    curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    
    // Headers maybe not needed ???    
    list = curl_slist_append(list, "Accept: application/json, text/javascript, */*; q=0.01");
    list = curl_slist_append(list, "X-Requested-With: XMLHttpRequest");
    
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
 
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));


    curl_slist_free_all(list); /* free the list again */


    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}
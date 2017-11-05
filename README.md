# grep_improved

Simple sequential ranked search process that processes text files, treating each input line as a possible match string, and generating a score for each line relative to a supplied query. Once all of the scores have been generated, the best-matching lines are output, in decreasing score order – a bit like whole documents are scored and ranked in web search engines such as Google and Bing.

Instructions to run it:
$ make
$ ./grep_improved "query" < Alice_Adventures_in_Wonderland.txt

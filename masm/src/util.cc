#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <getopt.h>
#define DEBUG
#include "util.hh"
#include "global.hh"

void show_line(int line,char* filename)
{
    std::string line_str;
    line_str = "";
    line_str+="./bin/sed.sh '";
    char temp[10];
    sprintf(temp,"%d",line);
    line_str+=temp;
    line_str+="p' ";
    line_str+=filename;
    line_str+=".temp.asm";
    system(line_str.c_str());
}
void print_blank(int column)
{
    int i=0;
    for(i=0;i<column-1;i++)
        printf(" ");
    fprintf(stdout, "\033[32m" "^\n" "\033[0m");
}

// use getopt_long to handle arguments
// -h       show help
// -v       show version
// -o file  place results to file
// -d file  dump AST to file
bool handle_opt(int argc, char** argv)
{
    int c;
    int version_flag = 0;
    int help_flag = 0;
    struct option long_options[] =
    {
        {"version", no_argument, &version_flag, 'v'},
        {"help", no_argument, &help_flag, 'h'},
        {"dump", required_argument, NULL, 'd'},
        {0, 0, 0, 0}
    };
    int option_index = 0;
    opterr = 0;

    while ((c = getopt_long(argc, argv, ":hvo:d:", long_options, &option_index)) != -1) {
        switch (c)
        {
            case 0:
                break;
            case 'h':
                help_flag = 1;
                break;
            case 'v':
                version_flag = 1;
                break;
            case 'o':
                outfile_name = optarg;
                break;
            case 'd':
                dumpfile_name = optarg;
                break;
            case '?':
                error("Unknown option -%c\n", optopt);
                return false;
            case ':':
                if (optopt == 'o')
                    error("Option -o requires an argument\n");
                else if (optopt == 'd')
                    error("Option -d requires an argument\n");
                else
                    error("Unknown option -%c\n", optopt);
                return false;
            default:
                error("Error in handle_opt()\n");
        }
    }

    if (help_flag)
    {
        printf("usage: parser  [options] [file]\n");
        printf("-h  --help     print this usage and exit\n");
        printf("-v  --version  print version and exit\n");
        printf("-o <file>      place the output into <file>\n");
        printf("-d <file>      dump AST into <file>\n");
        return false;
    }
    if (version_flag)
    {
        printf("parser V5.8 & AST & dumpdot\n");
        return false;
    }
    if (optind < argc)
        infile_name = argv[optind];
    if (infile_name == NULL)
        infp = stdin;
    else
    {
        ////////////////////////////
        /* change '\t' with 8 ' ' and change 'A'~'Z' to 'a'~'z'*/
        ////////////////////////////
        FILE *tempinfp,*tempoutfp;
        char *tempfile_name = (char *)malloc(sizeof(char)*(strlen(infile_name)+strlen(".temp.asm")+1));
        tempinfp = fopen(infile_name, "r");
        strcpy(tempfile_name,infile_name);
        strcat(tempfile_name,".temp.asm");
        tempoutfp = fopen(tempfile_name, "w");

        if (tempoutfp == NULL)
        {
            error("Can not open infile %s\n", infile_name);
            return false;
        }
        char ch;
        while((ch=fgetc(tempinfp))!=EOF)   
        { 
            if(ch == '\t')
            {
                ch = ' ';
                fputc(ch,tempoutfp);
                fputc(ch,tempoutfp);
                fputc(ch,tempoutfp);
                fputc(ch,tempoutfp);
            }
            else if(ch >='A' && ch <= 'Z')
            {
                ch+=32;
                fputc(ch,tempoutfp);
            }
            else{
                fputc(ch,tempoutfp);
            }
        } 
        fclose(tempinfp); 
        fclose(tempoutfp);
        ////////////////////////////////
        /* change '\t' with 8 ' ' and change 'A'~'Z' to 'a'~'z' end */
        ////////////////////////////////
        infp = fopen(tempfile_name, "r");
        if (infp == NULL)
        {
            error("Can not open infile %s\n",tempfile_name);
            return false;
        }
    }
    if (outfile_name == NULL)
        outfp = stdout;
    else
    {
        outfp = fopen(outfile_name, "w");
        if (outfp == NULL)
        {
            error("Can not open outfile %s\n", outfile_name);
            return false;
        }
        
    }
    if (dumpfile_name == NULL)
        dumpfp = NULL;
    else
    {
        callfile_name = (char *)malloc(strlen("callgraph.dot")+1);
        strcpy(callfile_name,"callgraph.dot");
        callfp = fopen(callfile_name, "w");
        if (callfp == NULL)
        {
            error("Can not open callfile %s\n", callfile_name);
            return false;
        }
        dumpfp = fopen(dumpfile_name, "w");
        if (dumpfp == NULL)
        {
            error("Can not open dumpfile %s\n", dumpfile_name);
            return false;
        }
    }
    return true;
}

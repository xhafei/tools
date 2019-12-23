set nu
syntax on
set cindent

set ts=4
set softtabstop=4
set shiftwidth=4
set expandtab
set autoindent

ab .i #include<iostream>
ab .u using namespace std;
ab .m int main(){}
ab .I #include<
ab .r return 0;

nmap <silent> <F5> gg=G

set fileencodings=utf-8,gb2312,gbk,gb18030
set termencoding=utf-8


/*
 * Programing Language C-- "Compiler"
 *    Tokuyama kousen Educational Computer 16bit Ver.
 *
 * Copyright (C) 2002-2019 by
 *                      Dept. of Computer Science and Electronic Engineering,
 *                      Tokuyama College of Technology, JAPAN
 *
 *   上記著作権者は，Free Software Foundation によって公開されている GNU 一般公
 * 衆利用許諾契約書バージョン２に記述されている条件を満たす場合に限り，本ソース
 * コード(本ソースコードを改変したものを含む．以下同様)を使用・複製・改変・再配
 * 布することを無償で許諾する．
 *
 *   本ソースコードは＊全くの無保証＊で提供されるものである。上記著作権者および
 * 関連機関・個人は本ソースコードに関して，その適用可能性も含めて，いかなる保証
 * も行わない．また，本ソースコードの利用により直接的または間接的に生じたいかな
 * る損害に関しても，その責任を負わない．
 *
 *
 */

/*
 * util.c : 良く使う関数
 *
 * 2019.03.10         : 構文解析器をparser，字句解析器をlexerに名称変更
 * 2016.09.14         : setFname() を追加
 * 2016.06.04         : eOpen() を追加
 * 2016.03.01         : NULL を null に書き換え
 * 2016.02.24         : strEndsWith 関数のバグ訂正
 * 2016.02.05 v3.0.0  : トランスレータと統合(strEndsWith 関数を追加)
 * 2012.12.30         : error2 を追加
 * 2010.07.20         : Subversion による管理を開始
 * 2009.07.21 v.0.8   : string 型の使用を廃止
 * 2008.08.26 v.0.6   : エラーメッセージにファイル名を追加
 * 2007.09.20 v.0.5   : 初期バージョン
 *
 * $Id$
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <unistd.h>

#include "lexer.h"
#include "util.h"

/* エラーメッセージに必要なファイル名を管理する */
static char fname[StrMAX + 1];                     // 入力ファイル名
void setFname(char s[]) {                          // 入力ファイル名を記憶する
  int i;
  for (i=0; i<=StrMAX; i=i+1) {
    fname[i] = s[i];
    if (fname[i]=='\0') break;
  }
  if (fname[i]!='\0') error("ファイル名が長すぎる");
}

/* エラーメッセージを表示して終了する */
void errmsg() {
  fprintf(stderr,"\"%s\": %d : ", fname, lxGetLn());
}

void error(char s[]) {
  int is_tty = isatty(fileno(stderr));
  if (is_tty) fprintf(stderr, "\x1b[31m");
  errmsg();
  fprintf(stderr,"%s\n", s);
  if (is_tty) fprintf(stderr, "\x1b[0m");
  exit(1);
}

void error2(char s1[], char s2[]) {
  int is_tty = isatty(fileno(stderr));
  if (is_tty) fprintf(stderr, "\x1b[31m");
  errmsg();
  fprintf(stderr,"%s : %s\n", s2, s1);
  if (is_tty) fprintf(stderr, "\x1b[0m");
  exit(1);
}

/* 領域を割り当ててエラーチェック */
void *ealloc(int s) {
  void *p = malloc(s);
  if (p==null) {
    error("メモリ割り当て");
  }
  return p;
}

/* 以下は ctype.h にありそうで存在しない関数 */

/* 区切り記号かテスト */
int isDelim(int ch) {
  return !isalnum(ch) && ch!='_';                  /* アルファベット,'_'以外 */
}

/* 8進数字かテスト */
int isOdigit(int ch) {
  return '0' <= ch && ch <= '7';                   /* '0'〜'7'が8進数        */
}

/* 文字列の最後が一致しているか比較する */
boolean strEndsWith(char *str, char *suffix){
  int len1 = strlen(str);
  int len2 = strlen(suffix);
  if (len1<len2) return false;
  for(int i = 1; i <= len2; i++)
    if(str[len1-i]!=suffix[len2-i])
      return false;
  return true;
}

/* エラーチェック付きの fopen */
FILE *eOpen(char *fname, char *mod) {
  FILE *fp = fopen(fname, mod);
  if (fp==NULL) {
    perror(fname);
    exit(1);
  }
  return fp;
}

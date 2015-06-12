/*
 * Copyright (c) 2001,2002 Mike Matsnev.  All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice immediately at the beginning of the file, without modification,
 *    this list of conditions, and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Absolutely no warranty of function or purpose is made by the author
 *    Mike Matsnev.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * $Id: Unicode.h,v 1.8 2002/07/19 10:44:54 mike Exp $
 * 
 */

#ifndef UNICODE_H
#define UNICODE_H

template<class T>
class Buffer
{
  struct Buf {
    int	    m_refs;
    //T	    *m_data;
  };
  T	    *m_data;
  Buf	    *buf() const { return ((Buf*)m_data)-1; }
  int	    m_size;
  void	    grab() const {
    if (m_data)
      ++buf()->m_refs;
  }
  void	    release() {
    if (m_data) {
      if (--buf()->m_refs==0)
	delete[] buf();
      m_data=0;
    }
  }
public:
  Buffer() : m_data(0), m_size(0) { }
  Buffer(const Buffer& b) : m_data(b.m_data), m_size(b.m_size) { grab(); }
  Buffer(int n) : m_size(n), m_data(0) {
    if (n) {
      m_data=(T*)(new Buf[(sizeof(T)*n+sizeof(Buf)-1)/sizeof(Buf)+1]+1);
      buf()->m_refs=1;
    }
  }
  Buffer(const T *p,int n) : m_size(n), m_data(0) {
    if (n) {
      m_data=(T*)(new Buf[(sizeof(T)*n+sizeof(Buf)-1)/sizeof(Buf)+1]+1);
      buf()->m_refs=1;
      memcpy(m_data,p,sizeof(T)*n);
    }
  }
  ~Buffer() { release(); }
  Buffer<T>& operator=(const Buffer<T>& b) {
    b.grab();
    release();
    m_data=b.m_data;
    m_size=b.m_size;
    return *this;
  }
  operator T*() { return m_data; }
  operator const T*() const { return m_data; }
  int size() const { return m_size; }
  void setsize(int ns) { m_size=ns; }
  void Zero() { memset(m_data,0,m_size*sizeof(T)); }
};

class Unicode {
public:
  // conversion to unicode
  static int	      WCLength(int codepage,const char *mbstr,int mblen);
  static void	      ToWC(int codepage,const char *mbstr,int mblen,
    wchar_t *wcstr,int wclen);

  // conversion to system default codepage
  static int	      MBLength(const wchar_t *wcstr,int wclen);
  static void	      ToMB(const wchar_t *wcstr,int wclen,char *mbstr,int mblen);

  // convenience functions
  static Buffer<wchar_t>  ToWCbuf(int codepage,const char *mbstr,int mblen);
  static Buffer<char>	  ToMBbuf(const wchar_t *wcstr,int wclen);

  // MFC interface
  static CString	  ToCS(const wchar_t *wcstr,int wclen);
  static CString	  ToCS(const Buffer<wchar_t>& wcbuf) {
    return ToCS(wcbuf,wcbuf.size());
  }
  static CString	  ToCS(int codepage,const char *mbstr,int mblen) {
    return ToCS(ToWCbuf(codepage,mbstr,mblen));
  }

  static Buffer<wchar_t>  ToWCbuf(const CString& str);
  static Buffer<wchar_t>  ToWCbufZ(const CString& str);

  // codepages support
  static int		  GetNumCodePages();
  static const TCHAR	  *GetCodePageName(int num);
  static const wchar_t	  *GetCodePageNameW(int num);
  static int		  GetIntCodePage(UINT mscp);
  static UINT		  GetMSCodePage(int cp);
  static int		  FindCodePage(const TCHAR *name);
  static int		  DefaultCodePage();
  static const wchar_t	  *GetTable(int cp); // only for builtin encodings

  // codepage detection
  static int	      DetectCodePage(const char *mbstr,int mblen);

  // case conversion
  static Buffer<wchar_t>  Lower(const Buffer<wchar_t>& str);

  // sortkey generation
  static Buffer<char>  SortKey(LCID lcid,const wchar_t *str,int len);
  static Buffer<char>  SortKey(LCID lcid,const wchar_t *str) {
    return SortKey(lcid,str,wcslen(str));
  }
};

#endif

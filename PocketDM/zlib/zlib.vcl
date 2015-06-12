<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: zlib - Win32 (WCE x86em) Debug--------------------
</h3>
<h3>Command Lines</h3>
warning: unresolved Environment Variable  "$(EXTRACFLAGS)"
Creating temporary file "D:\DOCUME~1\Tdg\LOCALS~1\Temp\RSP2BBD.tmp" with contents
[
/nologo /W3 /Zi /Od /D "DEBUG" /D _WIN32_WCE=300 /D "WIN32" /D "STRICT" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "WIN32_PLATFORM_PSPC" /D "i486" /D UNDER_CE=300 /D "UNICODE" /D "_UNICODE" /D "_X86_" /D "x86" /D "_LIB" /Fo"X86EMDbg/" /Fd"X86EMDbg/" /Gz  /c 
"D:\Work\Private\DM\PocketDM\zlib\trees.c"
]
Creating command line "cl.exe @D:\DOCUME~1\Tdg\LOCALS~1\Temp\RSP2BBD.tmp" 
Creating temporary file "D:\DOCUME~1\Tdg\LOCALS~1\Temp\RSP2BBE.tmp" with contents
[
/nologo /out:"X86EMDbg\zlib.lib" 
.\X86EMDbg\adler32.obj
.\X86EMDbg\crc32.obj
.\X86EMDbg\infblock.obj
.\X86EMDbg\infcodes.obj
.\X86EMDbg\inffast.obj
.\X86EMDbg\inflate.obj
.\X86EMDbg\inftrees.obj
.\X86EMDbg\infutil.obj
.\X86EMDbg\uncompr.obj
.\X86EMDbg\zutil.obj
.\X86EMDbg\gzio.obj
.\X86EMDbg\compress.obj
.\X86EMDbg\deflate.obj
.\X86EMDbg\trees.obj
]
Creating command line "link.exe -lib @D:\DOCUME~1\Tdg\LOCALS~1\Temp\RSP2BBE.tmp"
<h3>Output Window</h3>
Compiling...
trees.c
Creating library...



<h3>Results</h3>
zlib.lib - 0 error(s), 0 warning(s)
</pre>
</body>
</html>

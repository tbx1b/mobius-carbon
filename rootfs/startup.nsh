@echo -off
mode 1920 1080

cls
if exist .\System\Stash\BootPicker.pcsw then
 .\System\Stash\BootPicker.pcsw
 goto END
endif

if exist fs0:\System\Stash\BootPicker.pcsw then
 fs0:
 System\Stash\BootPicker.pcsw
 goto END
endif

if exist fs1:\System\Stash\BootPicker.pcsw then
 fs1:
 System\Stash\BootPicker.pcsw
 goto END
endif

if exist fs2:\System\Stash\BootPicker.pcsw then
 fs2:
 System\Stash\BootPicker.pcsw
 goto END
endif

if exist fs3:\System\Stash\BootPicker.pcsw then
 fs3:
 System\Stash\BootPicker.pcsw
 goto END
endif

if exist fs4:\System\Stash\BootPicker.pcsw then
 fs4:
 System\Stash\BootPicker.pcsw
 goto END
endif

if exist fs5:\System\Stash\BootPicker.pcsw then
 fs5:
 System\Stash\BootPicker.pcsw
 goto END
endif

if exist fs6:\System\Stash\BootPicker.pcsw then
 fs6:
 System\Stash\BootPicker.pcsw
 goto END
endif

if exist fs7:\System\Stash\BootPicker.pcsw then
 fs7:
 System\Stash\BootPicker.pcsw
 goto END
endif

 echo "Unable to find bootloader".
 
:END

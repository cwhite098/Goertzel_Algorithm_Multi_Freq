## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd package/cfg/Sys_BIOs_config_pe66.oe66

linker.cmd: package/cfg/Sys_BIOs_config_pe66.xdl
	$(SED) 's"^\"\(package/cfg/Sys_BIOs_config_pe66cfg.cmd\)\"$""\"C:/Users/chris/OneDrive/Uni/Year2/C_for_Embedded_Systems/GTZ_all_freq/.config/xconfig_Sys_BIOs_config/\1\""' package/cfg/Sys_BIOs_config_pe66.xdl > $@

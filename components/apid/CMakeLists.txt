set(srcs "src/io.c" "src/crono.c")
idf_component_register( SRCS "${srcs}"
					INCLUDE_DIRS ".."
					REQUIRES driver nvs_flash)
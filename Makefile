name=toggleIndentMarkers
installPath=~/.config/geany/plugins/

.PHONY:all clean build install uninstall

all:install

build:
	gcc -c $(name).c -fPIC `pkg-config --cflags geany`
	gcc $(name).o -o$(name).so -shared `pkg-config --libs geany`

clean:
	rm $(name).*o

install:build
	cp $(name).so $(installPath)

uninstall:
	rm $(installPath)/$(name).so

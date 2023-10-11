compile:
	ninja -vC build -j13

test:
	MESON_TESTTHREADS=13 meson test -C build

clean:
	ninja -vC build clean

server: compile
	./build/src/server/server

client: compile
	./build/src/client-tui/client-tui 127.0.0.1

compile:
	ninja -vC build -j13

clean:
	ninja -vC build clean

server: compile
	./build/src/server/server

client: compile
	./build/src/client-tui/client-tui

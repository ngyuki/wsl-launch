
all: wsl-launch.exe

wsl-launch.exe: main.c
	x86_64-w64-mingw32-gcc $< -O2 -municode -lshlwapi -o $@

clean:
	rm -f wsl-launch.exe

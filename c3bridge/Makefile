PRJ=c3bridge

build:
	mkdir -p _build
	sh -c "cd _build; unset MAKELEVEL; cmake ..; make"
upload: build
	sudo `which picotool` load _build/$(PRJ).uf2 -f

connect:
	cu -l /dev/pico --nostop


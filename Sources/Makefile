.PHONY: all clean

all:
	cd litgen-model/ && $(MAKE)
	echo ==== litgen-model all done!
	cd litgen-tg/ && $(MAKE)
	echo ==== litgen-tg all done!

clean:
	cd ../litgen-model && $(MAKE) clean
	echo ==== litgen-model clean all done!
	cd ../litgen-tg && $(MAKE) clean
	echo ==== litgen-tg clean all done!



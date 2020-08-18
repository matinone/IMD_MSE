ifneq ($(KERNELRELEASE),)
obj-m := esp32_driver.o
else
KDIR := $(HOME)/MAESTRIA/MSE/imd/linux
all:
	$(MAKE) -C $(KDIR) M=$$PWD

.PHONY: clean
clean:
	rm -f *.mod* *.o *.ko modules.order Module.symvers

endif

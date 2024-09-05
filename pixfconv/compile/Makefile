OUTPUT = pixfconv_st.so

CC = cc -fPIC -shared
LINK =

debug:
	$(CC) -Dset_st -g root.h -o $(OUTPUT) $(LINK)

release:
	$(CC) -s -O3 root.h -o $(OUTPUT) $(LINK)

clean:
	rm $(OUTPUT)

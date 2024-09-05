OUTPUT = pixfconv_st.so

CC = cc -fPIC -shared
LINK =

debug:
	$(CC) -Dset_st -g root.c -o $(OUTPUT) $(LINK)

release:
	$(CC) -Dset_st -s -O3 root.c -o $(OUTPUT) $(LINK)

clean:
	rm $(OUTPUT)

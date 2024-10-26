#include "ccsb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct strBuf {
    char* content;
    int capacity;
    int used;
};

StrBuf NewSB(char* str) {
	size_t size = strlen(str);
	StrBuf sb = malloc(sizeof(struct strBuf));
	if(sb == NULL) {
	    return NULL;
	}
	sb->capacity = size*2;
	sb->used = size;
	sb->content = malloc(2*size);
	if(sb->content == NULL) {
	    free(sb);
	    return NULL;
	}
	memcpy(sb->content, str, size);
	return sb;
}

int writeSB(StrBuf sb, char* str) {
	size_t size = strlen(str);
	if(size + sb->used >= sb->capacity) {
		sb->capacity = (sb->used + size) * 2;
		char* novo = malloc(sb->capacity*sizeof(char));
		if(novo == NULL) {
		    return -1;
		}
		memcpy(novo, sb->content, sb->used);
		free(sb->content);
		sb->content = novo;
	}
	memcpy(&sb->content[sb->used], str, size);
	sb->used += size;
	return 0;
}

int writeByteSB(StrBuf sb, char c) {
    char* v = malloc(sizeof(c));
    v[0] = c;
    int r = writeSB(sb, v);
    if(r < 0) {
        return r;
    }
    return 0;
}

int setCapSB(StrBuf sb, int size) {
    sb->capacity = size;
	char* novo = malloc(sb->capacity*sizeof(char));
	if(novo == NULL) {
	    return -1;
	}
	memcpy(novo, sb->content, size);
	free(sb->content);
	if(sb->used > sb->capacity) {
	   sb->used = sb->capacity;
	}
	sb->content = novo;
	return 0;
}

int getCapSB(StrBuf sb) {
    printf("%d\n", sb == NULL);
    return sb->capacity;
}

int getLenSB(StrBuf sb) {
    return sb->used;
}

char* getContentSB(StrBuf sb) {
	char* ret = malloc((sb->used + 1)*sizeof(char));
	if(ret == NULL) {
		return NULL;
	}
	memcpy(ret, sb->content, sb->used);
	ret[sb->used] = '\0';
	return ret;
}

int resetSB(StrBuf sb) {
	sb->used = 0;
	char* novo = malloc(sb->capacity*sizeof(char));
	if(novo == NULL) {
	    return -1;
	}
	free(sb->content);
	sb->content = novo;
	return 0;
}

void destroySB(StrBuf* sb) {
    if (sb == NULL || *sb == NULL) return;
    free((*sb)->content);
    free(*sb);
    *sb = NULL;
}

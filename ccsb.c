#include "ccsb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static float defaultGrow = 2.0;

struct strBuf {
    char* content;
    int capacity;
    int used;
    float growFactor;
};

StrBuf newGrowFactorSB(char* str, float growFactor) {
   	size_t size = strlen(str);
	StrBuf sb = malloc(sizeof(struct strBuf));
	if(sb == NULL) {
        perror("fail during memory allocation.\n");
	    return NULL;
	}
	if(growFactor < 1 || growFactor > 10) {
	    perror("growFactor must to be between 1 and 10.\n");
	    return NULL;
	}
	sb->growFactor = growFactor;
	sb->capacity = size*sb->growFactor;
	sb->used = size;
	sb->content = malloc(sizeof(char)*sb->capacity);
	if(sb->content == NULL) {
	    perror("fail during memory allocation.\n");
	    free(sb);
	    return NULL;
	}
	memcpy(sb->content, str, size);
	return sb;
}

StrBuf newSB(char* str) {
	return newGrowFactorSB(str, defaultGrow);
}

int writeSB(StrBuf sb, char* str) {
	size_t size = strlen(str);
	if(size + sb->used >= sb->capacity) {
		sb->capacity = (sb->used + size) * sb->growFactor;
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
	    perror("fail during memory allocation.\n");
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
    return sb->capacity;
}

int getLenSB(StrBuf sb) {
    return sb->used;
}

char* getContentSB(StrBuf sb) {
	char* ret = malloc((sb->used + 1)*sizeof(char));
	if(ret == NULL) {
	    perror("fail during memory allocation.\n");
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
	    perror("fail during memory allocation.\n");
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

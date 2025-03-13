bool bytess2[length][8];
    blocks_to_bytes(3, 2, blocks2, length, bytess2);
    for(int j = 0; j < length; j++){
        for(int i = 0; i < 8; i++){
            printf("%d", bytess2[j][i]);
        }
        printf("\n");
    }
    // prints:
    // 01000001
    // 01101000
    // 01101111
    // 01101010
    // 00000000
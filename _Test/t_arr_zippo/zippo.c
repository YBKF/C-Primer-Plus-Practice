#include <stdio.h>

int main(int argc, char const *argv[])
{
    int zippo[4][2] = {{00, 01}, {10, 11}, {20, 21}, {30, 31}};
    printf("Address of zippo, sizeof: %#p, %zd\n", zippo, sizeof zippo);

    printf("Address of zippo[0], sizeof: %#p, %zd\n", zippo[0], sizeof zippo[0]);

    printf("Address of zippo[0][0], sizeof: %#p, %zd\n", &zippo[0][0], sizeof zippo[0][0]);

    for (int i_outer = 0; i_outer < 4; i_outer++)
    {
        printf("zippo[%d]: %#p, data: %d\n", i_outer, &zippo[i_outer], *zippo[i_outer]);
        for (int i_inner = 0; i_inner < 3; i_inner++)
        {
            printf("zippo[%d][%d]: %#p, data: %d\n", i_outer, i_inner, &zippo[i_outer][i_inner], zippo[i_outer][i_inner]);
        }
    }

    return 0;
}

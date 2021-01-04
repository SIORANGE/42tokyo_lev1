
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int		main(void)
{
	int is_re = 1;
	while (is_re)
	{
		char str[100];
		int  a[5] = {0};
		printf("\n\n\n");
		printf("【　IP or mask　】        :　");scanf("%s",str);
		printf("\n\n\n");
		printf("〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜");
		printf("\n\n\n");
		int j = 0;
		for (int i=0;str[i] != '\0';i++)
		{
			if (str[i] == '.' || str[i] == '/')
				a[j++] = i;
		}
		if (a[3] == 0){
			unsigned int mask = ((unsigned int)atol(str) << (8*3))\
								+ ((unsigned int)atol(&str[a[0]+1]) << (8*2))\
								+ ((unsigned int)atol(&str[a[1]+1]) << (8*1))\
								+ ((unsigned int)atol(&str[a[2]+1]));
			unsigned int bits = (unsigned int)((long long)pow(2,32) - 1);
			unsigned int xmask = mask ^ bits;
			unsigned int count = 0;
			unsigned int x = 1;
			while (x & xmask)
			{
				x = x << 1;
				count++;
			}
			printf("最大のホスト数　          ：　%u",(unsigned int)pow(2,count) - 2);
			printf("\n\n\n");
		}else{
			unsigned int ip = ((unsigned int)atol(str) << (8*3))\
								+ ((unsigned int)atol(&str[a[0]+1]) << (8*2))\
								+ ((unsigned int)atol(&str[a[1]+1]) << (8*1))\
								+ ((unsigned int)atol(&str[a[2]+1]));
			unsigned int bits1 = (unsigned int)((long long)pow(2,32) - 1);
			unsigned int bits2 = pow(2,8) - 1;
			unsigned int mask_n = (unsigned int)atol(&str[a[3]+1]);
			unsigned int mask = bits1 << (32 - mask_n);
			unsigned int n_a = ip & mask;
			printf("ネットワークアドレス　    :　%u.%u.%u.%u  \n\n" , (n_a >> 24) & bits2\
															, (n_a >> 16) & bits2\
															, (n_a >> 8) & bits2\
															, n_a & bits2);
			unsigned int b_a = ip | (~mask);
			printf("ブロードキャストアドレス　:　%u.%u.%u.%u  \n\n" , (b_a >> 24) & bits2\
															, (b_a >> 16) & bits2\
															, (b_a >> 8) & bits2\
															, b_a & bits2);
			unsigned int add = n_a + 1;
			printf("ホストレンジ　            :　%u.%u.%u.%u - " , (add >> 24) & bits2\
															, (add >> 16) & bits2\
															, (add >> 8) & bits2\
															, add & bits2);
			unsigned int count = 1;
			while (add + 1 != b_a)
			{
				add++;
				count++;
			}
			printf("%u.%u.%u.%u \n\n" , (add >> 24) & bits2\
									, (add >> 16) & bits2\
									, (add >> 8) & bits2\
									, add & bits2);
			printf("最大のホスト数　          :　%u\n",count);
			printf("\n\n\n\n");
		}
		printf("〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜\n");
		printf("終わるなら「０」を入力してください。\n継続する場合は「０」以外の数値を入力してください\n\n もう一回やりますか？　：　");scanf("%d",&is_re);scanf("%*c");
	}
}
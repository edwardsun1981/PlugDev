///////////////////////////////////////////////////////////////
// Plug.h
// 建立时间: 2025.2.19
// 作者: 孙华庆		SunHuaQing
// 版本:
///////////////////////////////////////////////////////////////
#pragma once
inline bool is_utf8(unsigned char* data, int len)
{
	auto pre_num = [](unsigned char byte)
	{
		unsigned char mask = 0x80;
		int num = 0;
		for (int i = 0; i < 8; i++)
		{
			if ((byte & mask) == mask)
			{
				mask = mask >> 1;
				num++;
			}
			else
			{
				break;
			}
		}
		return num;
	};

	int num = 0;
	int i = 0;
	while (i < len)
	{
		if ((data[i] & 0x80) == 0x00)
		{
			// 0XXX_XXXX
			i++;
			continue;
		}
		else if ((num = pre_num(data[i])) > 2)
		{
			// 110X_XXXX 10XX_XXXX
			// 1110_XXXX 10XX_XXXX 10XX_XXXX
			// 1111_0XXX 10XX_XXXX 10XX_XXXX 10XX_XXXX
			// 1111_10XX 10XX_XXXX 10XX_XXXX 10XX_XXXX 10XX_XXXX
			// 1111_110X 10XX_XXXX 10XX_XXXX 10XX_XXXX 10XX_XXXX 10XX_XXXX
			// preNUm() 返回首个字节8个bits中首0bit前面1bit的个数，该数量也是该字符所使用的字节数
			i++;
			for (int j = 0; j < num - 1; j++)
			{
				//判断后面num - 1 个字节是不是都是10开
				if ((data[i] & 0xc0) != 0x80)
				{
					return false;
				}
				i++;
			}
		}
		else
		{
			//其他情况说明不是utf-8
			return false;
		}
	}
	return true;
};

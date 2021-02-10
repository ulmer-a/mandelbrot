#include "ResourceManager.h"

#include <cstring>

ResourceManager* ResourceManager::s_instance = nullptr;

static char encodeTable[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                            'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                            'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                            'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                            'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                            'w', 'x', 'y', 'z', '0', '1', '2', '3',
                            '4', '5', '6', '7', '8', '9', '+', '/'};
static char decodeTable[256];

static void buildDecodeTable()
{
  for (int i = 0; i < 64; i++)
    decodeTable[(unsigned char)encodeTable[i]] = i;
}

ResourceManager::ResourceManager()
{
  buildDecodeTable();
}

void* base64_decode(const char* data, size_t& outputLength)
{
  size_t dataLength = strlen(data);

  if (dataLength % 4 != 0)
    return nullptr;

  outputLength = dataLength / 4 * 3;
  unsigned char* decoded_data = new unsigned char[outputLength + 1];

  if (data[dataLength - 1] == '=') (outputLength)--;
  if (data[dataLength - 2] == '=') (outputLength)--;

  if (decoded_data == nullptr)
    return nullptr;

  for (int i = 0, j = 0; i < dataLength;)
  {
    uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decodeTable[data[i++]];
    uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decodeTable[data[i++]];
    uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decodeTable[data[i++]];
    uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decodeTable[data[i++]];

    uint32_t triple = (sextet_a << 3 * 6)
    + (sextet_b << 2 * 6)
    + (sextet_c << 1 * 6)
    + (sextet_d << 0 * 6);

    if (j < outputLength) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
    if (j < outputLength) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
    if (j < outputLength) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
  }

  return (void*)decoded_data;
}

ResourceManager &ResourceManager::getInstance()
{
  if (s_instance == nullptr)
    s_instance = new ResourceManager();
  return *s_instance;
}

std::string ResourceManager::getString(const std::string &name)
{
  return std::string();
}

std::string ResourceManager::loadString(const char *data)
{
  size_t size;
  char* str = (char*)base64_decode(data, size);
  str[size] = 0;
  auto ret { std::string(str) };
  delete[] str;
  return ret;
}

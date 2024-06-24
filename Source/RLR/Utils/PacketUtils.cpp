#include "PacketUtils.h"
#include "../Chat/GameClient.h"
// 일반적인 Serialize 및 Deserialize 함수 구현
template<typename T>
void Serialize(const T& data, char*& buffer) {
    std::memcpy(buffer, &data, sizeof(T));
    buffer += sizeof(T);
}

template<typename T>
void Deserialize(T& data, const char*& buffer) {
    std::memcpy(&data, buffer, sizeof(T));
    buffer += sizeof(T);
}

// 배열에 대한 특수화 구현
void Serialize(const char* data, char*& buffer, size_t length) {
    std::memcpy(buffer, data, length);
    buffer += length;
}

void Deserialize(char* data, const char*& buffer, size_t length) {
    std::memcpy(data, buffer, length);
    buffer += length;
}

// 명시적 인스턴스화
template void Serialize<int32_t>(const int32_t& data, char*& buffer);
template void Deserialize<int32_t>(int32_t& data, const char*& buffer);

template void Serialize<uint8_t>(const uint8_t& data, char*& buffer);
template void Deserialize<uint8_t>(uint8_t& data, const char*& buffer);

template void Serialize<long>(const long& data, char*& buffer);
template void Deserialize<long>(long& data, const char*& buffer);

template void Serialize<bool>(const bool& data, char*& buffer);
template void Deserialize<bool>(bool& data, const char*& buffer);

template void Serialize<float>(const float& data, char*& buffer);
template void Deserialize<float>(float& data, const char*& buffer);

template void Serialize<MoveResponsePacket>(const MoveResponsePacket& data, char*& buffer);
template void Deserialize<MoveResponsePacket>(MoveResponsePacket& data, const char*& buffer);
template void Serialize<InventoryRequestPacket>(const InventoryRequestPacket& data, char*& buffer);
template void Deserialize<InventoryRequestPacket>(InventoryRequestPacket& data, const char*& buffer);
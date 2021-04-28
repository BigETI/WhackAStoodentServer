#include <algorithm>
#include <cassert>

#include <Exceptions/DeserializationFailedException.hpp>
#include <Static/UUIDs.hpp>

uuids::uuid& WhackAStoodentServer::UUIDs::CreateNewUUID(uuids::uuid& result)
{
	std::random_device random_device;
	std::array<int, std::mt19937::state_size> seed_data(std::array<int, std::mt19937::state_size>{});
	std::generate(std::begin(seed_data), std::end(seed_data), std::ref(random_device));
	std::seed_seq sequence(std::begin(seed_data), std::end(seed_data));
	std::mt19937 generator(sequence);
	return result = uuids::uuid_random_generator{ generator }();
}

std::vector<std::uint8_t>& WhackAStoodentServer::UUIDs::SerializeUUID(const uuids::uuid& uuid, std::vector<std::uint8_t>& result)
{
	std::size_t offset(result.size());
	result.resize(offset + DataSize);
	std::memcpy(result.data() + offset, uuid.as_bytes().data(), DataSize);
	return result;
}

std::span<std::uint8_t const> WhackAStoodentServer::UUIDs::DeserializeUUID(const std::span<std::uint8_t const>& bytes, uuids::uuid& result)
{
	if (bytes.size() < DataSize)
	{
		throw WhackAStoodentServer::DeserializationFailedException();
	}
	result = uuids::uuid(bytes.begin(), bytes.begin() + DataSize);
	return bytes.subspan<DataSize>();
}

#include <algorithm>
#include <cassert>

#include <Exceptions/DeserializationFailedException.hpp>
#include <Static/UUIDs.hpp>

/// <summary>
/// Creates a new UUID
/// </summary>
/// <param name="result">Result</param>
/// <returns>New UUID</returns>
uuids::uuid& WhackAStoodentServer::UUIDs::CreateNewUUID(uuids::uuid& result)
{
	std::random_device random_device;
	std::array<int, std::mt19937::state_size> seed_data(std::array<int, std::mt19937::state_size>{});
	std::generate(std::begin(seed_data), std::end(seed_data), std::ref(random_device));
	std::seed_seq sequence(std::begin(seed_data), std::end(seed_data));
	std::mt19937 generator(sequence);
	return result = uuids::uuid_random_generator{ generator }();
}

/// <summary>
/// Serializes UUID
/// </summary>
/// <param name="uuid">UUID</param>
/// <param name="result">Result</param>
/// <returns>Serialized UUID</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::UUIDs::SerializeUUID(const uuids::uuid& uuid, std::vector<std::uint8_t>& result)
{
	std::size_t offset(result.size());
	result.resize(offset + DataSize);
	std::memcpy(result.data() + offset, uuid.as_bytes().data(), DataSize);
	return result;
}

/// <summary>
/// Deserializes UUID from data
/// </summary>
/// <param name="bytes">Data</param>
/// <param name="result">Result</param>
/// <returns>Remaining data to be deserialized</returns>
std::span<const std::uint8_t> WhackAStoodentServer::UUIDs::DeserializeUUID(std::span<const std::uint8_t> bytes, uuids::uuid& result)
{
	if (bytes.size() < DataSize)
	{
		throw WhackAStoodentServer::DeserializationFailedException();
	}
	result = uuids::uuid(bytes.begin(), bytes.begin() + DataSize);
	return bytes.subspan<DataSize>();
}

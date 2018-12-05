#include "pch.h"
#include "BinarySerializer.h"

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/bitset.hpp>
#include <cereal/types/boost_variant.hpp>
#include <cereal/types/chrono.hpp>
#include <cereal/types/common.hpp>
#include <cereal/types/complex.hpp>
#include <cereal/types/deque.hpp>
#include <cereal/types/forward_list.hpp>
#include <cereal/types/functional.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/queue.hpp>
#include <cereal/types/set.hpp>
#include <cereal/types/stack.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/tuple.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/valarray.hpp>
#include <cereal/types/concepts/pair_associative_container.hpp>
#include <cereal/archives/binary.hpp>
#include <fstream>

namespace binary_serialization
{

	BinarySerializer::BinarySerializer()
	{
	}


	BinarySerializer::~BinarySerializer()
	{
	}

	void BinarySerializer::Load(BinaryBlock& block)
	{
		std::ifstream os("out.cereal", std::ios::binary);
		cereal::BinaryInputArchive archive(os);
		archive(block);
	}

	void BinarySerializer::Save(BinaryBlock& block)
	{
		ofstream os(block.FilePath, ios::binary);
		cereal::BinaryOutputArchive archive(os);
		archive(block); // write
	}

	BinaryBlock& BinarySerializer::CreateBinaryBlock(const string& filepath, BinaryDataType type)
	{
		auto rb = new BinaryBlock();
		rb->Type = type;
		rb->FilePath = filepath;
		return *rb;
	}
}
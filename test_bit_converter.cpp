#include "bit_converter.h"

#include <gmock/gmock.h>

using ::testing::ElementsAreArray;
using ::testing::TestWithParam;
using ::testing::Values;

struct Int16ToBytesTestParam {
    int16_t                    input_value;
    std::vector<unsigned char> expected;
};
struct UInt16ToBytesTestParam {
    uint16_t                   input_value;
    std::vector<unsigned char> expected;
};

struct Int32ToBytesTestParam {
    int32_t                    input_value;
    std::vector<unsigned char> expected;
};
struct UInt32ToBytesTestParam {
    uint32_t                   input_value;
    std::vector<unsigned char> expected;
};

struct Int64ToBytesTestParam {
    int64_t                    input_value;
    std::vector<unsigned char> expected;
};
struct UInt64ToBytesTestParam {
    uint64_t                   input_value;
    std::vector<unsigned char> expected;
};

struct BytesToInt64TestParam {
    std::vector<unsigned char> input_value;
    int64_t                    expected;
};

class BitConverterInt16ToBytesTest : public TestWithParam<Int16ToBytesTestParam> {};
class BitConverterUInt16ToBytesTest : public TestWithParam<UInt16ToBytesTestParam> {};
class BitConverterInt32ToBytesTest : public TestWithParam<Int32ToBytesTestParam> {};
class BitConverterUInt32ToBytesTest : public TestWithParam<UInt32ToBytesTestParam> {};
class BitConverterInt64ToBytesTest : public TestWithParam<Int64ToBytesTestParam> {};
class BitConverterUInt64ToBytesTest : public TestWithParam<UInt64ToBytesTestParam> {};
class BitConverterBytesToInt64Test : public TestWithParam<BytesToInt64TestParam> {};

TEST_P(BitConverterInt16ToBytesTest, ConvertsCorrectly)
{
    Int16ToBytesTestParam param = GetParam();
    EXPECT_THAT(BitConverter::int16_to_bytes(param.input_value), ElementsAreArray(param.expected));
}
TEST_P(BitConverterUInt16ToBytesTest, ConvertsCorrectly)
{
    UInt16ToBytesTestParam param = GetParam();
    EXPECT_THAT(BitConverter::uint16_to_bytes(param.input_value), ElementsAreArray(param.expected));
}

TEST_P(BitConverterInt32ToBytesTest, ConvertsCorrectly)
{
    Int32ToBytesTestParam param = GetParam();
    EXPECT_THAT(BitConverter::int32_to_bytes(param.input_value), ElementsAreArray(param.expected));
}
TEST_P(BitConverterUInt32ToBytesTest, ConvertsCorrectly)
{
    UInt32ToBytesTestParam param = GetParam();
    EXPECT_THAT(BitConverter::uint32_to_bytes(param.input_value), ElementsAreArray(param.expected));
}

TEST_P(BitConverterInt64ToBytesTest, ConvertsCorrectly)
{
    Int64ToBytesTestParam param = GetParam();
    EXPECT_THAT(BitConverter::int64_to_bytes(param.input_value), ElementsAreArray(param.expected));
}
TEST_P(BitConverterUInt64ToBytesTest, ConvertsCorrectly)
{
    UInt64ToBytesTestParam param = GetParam();
    EXPECT_THAT(BitConverter::uint64_to_bytes(param.input_value), ElementsAreArray(param.expected));
}

TEST_P(BitConverterBytesToInt64Test, ConvertsCorrectly)
{
    BytesToInt64TestParam param = GetParam();
    EXPECT_EQ(BitConverter::bytes_to_int64(param.input_value), param.expected);
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    BitConverterTest,
    BitConverterInt16ToBytesTest,
    Values(
        Int16ToBytesTestParam{0, {0x00, 0x00}},
        Int16ToBytesTestParam{15, {0x0F, 0x00}},
        Int16ToBytesTestParam{-15, {0xF1, 0xFF}},
        Int16ToBytesTestParam{10000, {0x10, 0x27}},
        Int16ToBytesTestParam{-10000, {0xF0, 0xD8}},
        Int16ToBytesTestParam{-32768, {0x00, 0x80}},
        Int16ToBytesTestParam{32767, {0xFF, 0x7F}}
    )
);

INSTANTIATE_TEST_SUITE_P(
    BitConverterTest,
    BitConverterUInt16ToBytesTest,
    Values(
        UInt16ToBytesTestParam{0, {0x00, 0x00}},
        UInt16ToBytesTestParam{15, {0x0F, 0x00}},
        UInt16ToBytesTestParam{1023, {0xFF, 0x03}},
        UInt16ToBytesTestParam{10000, {0x10, 0x27}},
        UInt16ToBytesTestParam{32767, {0xFF, 0x7F}},
        UInt16ToBytesTestParam{65535, {0xFF, 0xFF}}
    )
);
INSTANTIATE_TEST_SUITE_P(
    BitConverterTest,
    BitConverterInt32ToBytesTest,
    Values(
        Int32ToBytesTestParam{0, {0x00, 0x00, 0x00, 0x00}},
        Int32ToBytesTestParam{15, {0x0F, 0x00, 0x00, 0x00}},
        Int32ToBytesTestParam{-15, {0xF1, 0xFF, 0xFF, 0xFF}},
        Int32ToBytesTestParam{1048576, {0x00, 0x00, 0x10, 0x00}},
        Int32ToBytesTestParam{-1048576, {0x00, 0x00, 0xF0, 0xFF}},
        Int32ToBytesTestParam{1000000000, {0x00, 0xCA, 0x9A, 0x3B}},
        Int32ToBytesTestParam{-1000000000, {0x00, 0x36, 0x65, 0xC4}},
        Int32ToBytesTestParam{INT32_MIN, {0x00, 0x00, 0x00, 0x80}},
        Int32ToBytesTestParam{2147483647, {0xFF, 0xFF, 0xFF, 0x7F}}
    )
);

INSTANTIATE_TEST_SUITE_P(
    BitConverterTest,
    BitConverterUInt32ToBytesTest,
    Values(
        UInt32ToBytesTestParam{0, {0x00, 0x00, 0x00, 0x00}},
        UInt32ToBytesTestParam{15, {0x0F, 0x00, 0x00, 0x00}},
        UInt32ToBytesTestParam{1023, {0xFF, 0x03, 0x00, 0x00}},
        UInt32ToBytesTestParam{1048576, {0x00, 0x00, 0x10, 0x00}},
        UInt32ToBytesTestParam{1000000000, {0x00, 0xCA, 0x9A, 0x3B}},
        UInt32ToBytesTestParam{2147483647, {0xFF, 0xFF, 0xFF, 0x7F}},
        UInt32ToBytesTestParam{4294967295U, {0xFF, 0xFF, 0xFF, 0xFF}}
    )
);

INSTANTIATE_TEST_SUITE_P(
    BitConverterTest,
    BitConverterInt64ToBytesTest,
    Values(
        Int64ToBytesTestParam{0, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
        Int64ToBytesTestParam{16777215, {0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00}},
        Int64ToBytesTestParam{-16777215, {0x01, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},
        Int64ToBytesTestParam{1000000000, {0x00, 0xCA, 0x9A, 0x3B, 0x00, 0x00, 0x00, 0x00}},
        Int64ToBytesTestParam{-1000000000, {0x00, 0x36, 0x65, 0xC4, 0xFF, 0xFF, 0xFF, 0xFF}},
        Int64ToBytesTestParam{4294967296, {0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00}},
        Int64ToBytesTestParam{-4294967296, {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF}},
        Int64ToBytesTestParam{187649984473770, {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00}},
        Int64ToBytesTestParam{-187649984473770, {0x56, 0x55, 0x55, 0x55, 0x55, 0x55, 0xFF, 0xFF}},
        Int64ToBytesTestParam{1000000000000000000, {0x00, 0x00, 0x64, 0xA7, 0xB3, 0xB6, 0xE0, 0x0D}},
        Int64ToBytesTestParam{-1000000000000000000, {0x00, 0x00, 0x9C, 0x58, 0x4C, 0x49, 0x1F, 0xF2}},
        Int64ToBytesTestParam{INT64_MIN, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80}},
        Int64ToBytesTestParam{INT64_MAX, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F}}
    )
);

INSTANTIATE_TEST_SUITE_P(
    BitConverterTest,
    BitConverterUInt64ToBytesTest,
    Values(
        UInt64ToBytesTestParam{0, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
        UInt64ToBytesTestParam{16777215, {0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00}},
        UInt64ToBytesTestParam{1000000000, {0x00, 0xCA, 0x9A, 0x3B, 0x00, 0x00, 0x00, 0x00}},
        UInt64ToBytesTestParam{4294967296, {0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00}},
        UInt64ToBytesTestParam{187649984473770, {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00}},
        UInt64ToBytesTestParam{1000000000000000000, {0x00, 0x00, 0x64, 0xA7, 0xB3, 0xB6, 0xE0, 0x0D}},
        UInt64ToBytesTestParam{10000000000000000000ULL, {0x00, 0x00, 0xE8, 0x89, 0x04, 0x23, 0xC7, 0x8A}},
        UInt64ToBytesTestParam{INT64_MAX, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F}},
        UInt64ToBytesTestParam{UINT64_MAX, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}}
    )
);

INSTANTIATE_TEST_SUITE_P(
    BitConverterTest,
    BitConverterBytesToInt64Test,
    Values(
        BytesToInt64TestParam{{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 0},
        BytesToInt64TestParam{{0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00}, 16777215},
        BytesToInt64TestParam{{0x01, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, -16777215},
        BytesToInt64TestParam{{0x00, 0xCA, 0x9A, 0x3B, 0x00, 0x00, 0x00, 0x00}, 1000000000},
        BytesToInt64TestParam{{0x00, 0x36, 0x65, 0xC4, 0xFF, 0xFF, 0xFF, 0xFF}, -1000000000},
        BytesToInt64TestParam{{0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00}, 4294967296},
        BytesToInt64TestParam{{0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF}, -4294967296},
        BytesToInt64TestParam{{0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00}, 187649984473770},
        BytesToInt64TestParam{{0x56, 0x55, 0x55, 0x55, 0x55, 0x55, 0xFF, 0xFF}, -187649984473770},
        BytesToInt64TestParam{{0x00, 0x00, 0x64, 0xA7, 0xB3, 0xB6, 0xE0, 0x0D}, 1000000000000000000},
        BytesToInt64TestParam{{0x00, 0x00, 0x9C, 0x58, 0x4C, 0x49, 0x1F, 0xF2}, -1000000000000000000},
        BytesToInt64TestParam{{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80}, INT64_MIN},
        BytesToInt64TestParam{{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F}, INT64_MAX}
    )
);
// clang-format on

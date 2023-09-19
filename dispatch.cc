#include <iostream>
#include <memory>
#include <tuple>
#include <type_traits>
#include <vector>

// tuple type
typedef std::tuple<std::vector<std::shared_ptr<int>>,
        std::vector<std::shared_ptr<bool>>,
        std::vector<std::shared_ptr<std::string>>,
        std::vector<std::shared_ptr<int64_t>>>
        tuple_type;

tuple_type data_tuple;

template <typename T>
struct VectorTypeHelper {};

template <typename T>
struct VectorTypeHelper<std::shared_ptr<T>> {
    typedef T type;
};

// get matched tuple index
template <typename WantType, typename TupleType, typename Index = std::integral_constant<std::size_t, 0>>
struct dataTypeIndex {
    static constexpr int value =
            std::is_same<WantType,
                    typename VectorTypeHelper<
                            typename std::tuple_element<Index::value, TupleType>::type::value_type>::type>::value
                    ? Index::value
                    : dataTypeIndex<WantType, TupleType, std::integral_constant<std::size_t, Index::value + 1>>::value;
};

template <typename WantType, typename TupleType>
struct dataTypeIndex<WantType, TupleType, std::integral_constant<std::size_t, std::tuple_size<TupleType>::value>> {
    static constexpr int value = -1;
};

// add to tuple if matched
template <typename T, std::size_t N = std::tuple_size<tuple_type>::value>
struct addToTupleIfMatched {
    static void add(std::shared_ptr<T> sp) {
        constexpr int index = dataTypeIndex<T, tuple_type>::value;
        if constexpr (index != -1)
            std::get<index>(data_tuple).push_back(sp);
        else
            addToTupleIfMatched<T, N - 1>::add(sp);
    }
};

template <typename T>
struct addToTupleIfMatched<T, 0> {
    static void add(std::shared_ptr<T> sp) {
        std::cout << "Type not matched.\n";
    }
};

template <typename T>
void addToTuple(std::shared_ptr<T> sp) {
    addToTupleIfMatched<T>::add(sp);
}

int main() {
    std::shared_ptr<int> spi = std::make_shared<int>(3);
    std::shared_ptr<bool> spb = std::make_shared<bool>(true);
    std::shared_ptr<std::string> sps = std::make_shared<std::string>("hello");
    std::shared_ptr<double> spd = std::make_shared<double>(3.14);

    addToTuple(spi);  // Will add to std::vector<std::shared_ptr<int>>
    addToTuple(spb);  // Will add to std::vector<std::shared_ptr<bool>>
    addToTuple(sps);  // Will add to std::vector<std::shared_ptr<std::string>>
    addToTuple(spd);  // Will print "Type not matched."

    return 0;
}

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <iostream>
#include <string>

struct Person {
    int id;
    std::string name;
    int age;

    Person(int id, const std::string& name, int age) : id(id), name(name), age(age) {}
};

// 命名空间简化
namespace bmi = boost::multi_index;

// 定义多索引容器
typedef bmi::multi_index_container<
    Person,
    bmi::indexed_by<
        // 按 ID 有序索引
        bmi::ordered_unique<bmi::member<Person, int, &Person::id>>,
        // 按姓名有序索引
        bmi::ordered_non_unique<bmi::member<Person, std::string, &Person::name>>,
        // 按年龄有序索引
        bmi::ordered_non_unique<bmi::member<Person, int, &Person::age>>
    >
> PersonContainer;

int main() {
    // 创建多索引容器
    PersonContainer persons;

    // 插入数据
    persons.insert(Person(1, "Alice", 30));
    persons.insert(Person(2, "Bob", 25));
    persons.insert(Person(3, "Alice", 22));

    // 按 ID 查询
    auto& id_index = persons.get<0>();
    std::cout << "By ID:" << std::endl;
    for (const auto& person : id_index) {
        std::cout << person.id << " " << person.name << " " << person.age << std::endl;
    }

    // 按姓名查询
    auto& name_index = persons.get<1>();
    std::cout << "\nBy Name:" << std::endl;
    for (auto it = name_index.equal_range("Alice").first; it != name_index.equal_range("Alice").second; ++it) {
        std::cout << it->id << " " << it->name << " " << it->age << std::endl;
    }

    return 0;
}

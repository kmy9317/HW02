// HW02.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// 이렇게 설계된 경우 파생클래스 생성시 Animal의 생성자->파생클래스 생성자 순으로 호출
// 소멸자 호출시 파생클래스의 소멸자 호출->기본 클래스 소멸자 호출
class Animal
{
public:
    // 기본 가상 소멸자
    virtual ~Animal() = default;
    // 추상 클래스로써 파생 클래스에서 makeSound를 구현하도록 함
    virtual void makeSound() = 0;
};

class Dog : public Animal
{
public:
    // 파생 클래스로써 알맞은 소리를 내도록 함수 오버라이드
    virtual void makeSound() override
    {
        cout << "멍멍" << endl;
    }
};

class Cat : public Animal
{
public:
    virtual void makeSound() override
    {
        cout << "냥냥" << endl;
    }
};

class Cow : public Animal
{
public:
    virtual void makeSound() override
    {
        cout << "음메" << endl;
    }
};

class Zoo 
{
private:
    Animal* animals[10]; 
    int animalCount = 0;

public:
    void addAnimal(Animal* animal)
    {
        // 용량 확인
        if (animalCount < 10)
        {
            animals[animalCount++] = animal;
        }
        else
        {
            // 에러 출력
            cerr << "동물원에 동물이 가득 찼습니다." << endl;
        }
    }

    void performActions()
    {
        for (int i = 0; i < animalCount; ++i) animals[i]->makeSound();
    }

    ~Zoo()
    {
        for (int i = 0; i < animalCount; ++i)
        {
            delete animals[i];
        }
        cout << "메모리 해제 완료" << endl;
    }
};

Animal* createRandomAnimal()
{
    // 랜덤 0, 1, 2를 받음
    int r = std::rand() % 3;

    // swithc문을 사용하여 값에 따라 객체 동적 할당
    switch (r) 
    {
    case 0: return new Dog();
    case 1: return new Cat();
    case 2: return new Cow();
    default: return nullptr; 
    }
}

int main()
{
    /***********
        필수
    ************/
    Animal* animals[3] = { new Dog(), new Cat(), new Cow() };
   
    for (auto* animal : animals)
    {
        animal->makeSound();
    }

    /***********
        도전
    ************/
    {
        // 필수에서 동적할당한 animals들을 Zoo 클래스에서 관리하도록 함
        // 해당 괄호 벗어날 경우 Zoo의 소멸자가 실행되면서 이전에 동적할당된 animals들이 메모리 해제 됨
        Zoo zoo;
        zoo.addAnimal(animals[0]);
        zoo.addAnimal(animals[1]);
        zoo.addAnimal(animals[2]);
    }
    // 랜덤화를 위한 현재 시간으로 시드값 설정.
    srand(time(0));

    // 랜덤으로 생성된 객체 포인터에 대한 sound 출력
    Animal* randomAnimal = createRandomAnimal();
    cout << "randomAnimal Sound: ";
    randomAnimal->makeSound();
}

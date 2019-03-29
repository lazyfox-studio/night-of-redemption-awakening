#include "../../Headers/Allies/Person.h"

void Person::move(int dx, int dy, int shift) {
    if ((dx != 0) && (dy != 0)) //Чтобы бег по диагонали не был быстрее чем по прямой
    {
        x += dx * (speed + (speed * shift)) * 0,707;
        y += dy * (speed + (speed * shift)) * 0,707;
        return;
    }
    x += dx * (speed + (speed * shift));
    y += dy * (speed + (speed * shift));
}

void Person::shoot() {

}

void Person::draw() {

}

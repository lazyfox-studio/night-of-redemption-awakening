#include "../../Headers/Allies/Person.h"

void Person::move(int dbx, int dby, int shift) {
    if ((dbx != 0) && (dby != 0)) //Чтобы бег по диагонали не был быстрее чем по прямой
    {
        float dx = dbx * (speed + (speed * shift)) * 0.707;
        float dy = dby * (speed + (speed * shift)) * 0.707;
        x = x + dx;
        y = y + dy;
        view.move(dx, dy);
        return;
    }
    float dx = dbx * (speed + (speed * shift));
    float dy = dby * (speed + (speed * shift));
    x = x + dx;
    y = y + dy;
    view.move(dx, dy);
}

void Person::shoot() {

}

void Person::draw() {

}

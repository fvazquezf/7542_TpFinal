#ifndef UPDATE_H
#define UPDATE_H

class Update {
private:
public:
    Update();

    virtual void serialize() = 0;

    virtual ~Update();
};


#endif

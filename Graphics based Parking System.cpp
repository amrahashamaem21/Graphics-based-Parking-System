
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;
class parking_block
{
private:
    string** slot;
    int* slots_per_row;
    int      total_rows;
    float    x_coordinate;
    float    y_coordinate;

public:
    parking_block()
    {
        slot = nullptr;
        slots_per_row = nullptr;
        total_rows = 0;
        x_coordinate = 0;
        y_coordinate = 0;
    }
    parking_block(int num_rows)
    {
        total_rows = num_rows;
        slots_per_row = new int[total_rows];
        slot = new string * [total_rows];
        for (int i = 0; i < total_rows; i++)
        {
            slot[i] = nullptr;
            slots_per_row[i] = 0;
        }
        x_coordinate = 0;
        y_coordinate = 0;
    }
    parking_block(const parking_block& p)
    {
        total_rows = p.total_rows;
        x_coordinate = p.x_coordinate;
        y_coordinate = p.y_coordinate;

        slots_per_row = new int[total_rows];
        slot = new string * [total_rows];

        for (int i = 0; i < total_rows; i++)
        {
            slots_per_row[i] = p.slots_per_row[i];
            if (p.slot[i] != nullptr)
            {
                slot[i] = new string[slots_per_row[i]];
                for (int j = 0; j < slots_per_row[i]; j++)
                    slot[i][j] = p.slot[i][j];
            }
            else slot[i] = nullptr;
        }
    }
    parking_block(parking_block&& p)
    {
        total_rows = p.total_rows;
        slot = p.slot;
        slots_per_row = p.slots_per_row;
        x_coordinate = p.x_coordinate;
        y_coordinate = p.y_coordinate;

        p.slot = nullptr;
        p.slots_per_row = nullptr;
        p.total_rows = 0;
        p.x_coordinate = 0;
        p.y_coordinate = 0;
    }
    parking_block& operator=(const parking_block& p)
    {
        if (this != &p)
        {
            if (slot != nullptr)
            {
                for (int i = 0; i < total_rows; i++) delete[] slot[i];
                delete[] slot;
            }
            if (slots_per_row != nullptr) delete[] slots_per_row;

            total_rows = p.total_rows;
            x_coordinate = p.x_coordinate;
            y_coordinate = p.y_coordinate;

            slots_per_row = new int[total_rows];
            slot = new string * [total_rows];

            for (int i = 0; i < total_rows; i++)
            {
                slots_per_row[i] = p.slots_per_row[i];
                if (p.slot[i] != nullptr)
                {
                    slot[i] = new string[slots_per_row[i]];
                    for (int j = 0; j < slots_per_row[i]; j++)
                        slot[i][j] = p.slot[i][j];
                }
                else slot[i] = nullptr;
            }
        }
        return *this;
    }
    parking_block& operator=(parking_block&& p)
    {
        if (this != &p)
        {
            if (slot != nullptr)
            {
                for (int i = 0; i < total_rows; i++) delete[] slot[i];
                delete[] slot;
            }
            if (slots_per_row != nullptr) delete[] slots_per_row;

            total_rows = p.total_rows;
            slot = p.slot;
            slots_per_row = p.slots_per_row;
            x_coordinate = p.x_coordinate;
            y_coordinate = p.y_coordinate;

            p.slot = nullptr;
            p.slots_per_row = nullptr;
            p.total_rows = 0;
        }
        return *this;
    }
    ~parking_block()
    {
        if (slot != nullptr)
        {
            for (int i = 0; i < total_rows; i++) delete[] slot[i];
            delete[] slot;
        }
        if (slots_per_row != nullptr) delete[] slots_per_row;
    }

    void add_rows(int n)
    {
        int* temp = new int[total_rows + n];
        for (int i = 0; i < total_rows; i++)       temp[i] = slots_per_row[i];
        for (int i = total_rows; i < total_rows + n; i++) temp[i] = 0;
        delete[] slots_per_row;

        string** new_slot = new string * [total_rows + n];
        for (int i = 0; i < total_rows; i++)       new_slot[i] = slot[i];
        for (int i = total_rows; i < total_rows + n; i++) new_slot[i] = nullptr;
        delete[] slot;

        slots_per_row = temp;
        slot = new_slot;
        total_rows += n;
    }

    void add_slots(int row_num, int n)
    {
        slot[row_num] = new string[n];
        for (int i = 0; i < n; i++) slot[row_num][i] = "empty";
        slots_per_row[row_num] = n;
    }
    string park_car(int row_num, int slot_num, string vehicle_num)
    {
        if (row_num < 0 || row_num >= total_rows)
            return "ERROR: Row " + to_string(row_num + 1) + " does not exist!";
        if (slot[row_num] == nullptr || slot_num < 0 || slot_num >= slots_per_row[row_num])
            return "ERROR: Slot " + to_string(slot_num + 1) + " does not exist!";
        if (slot[row_num][slot_num] != "empty")
            return "ERROR: Slot already occupied by " + slot[row_num][slot_num] + "!";

        slot[row_num][slot_num] = vehicle_num;
        return "SUCCESS: " + vehicle_num + " parked at Row " +
            to_string(row_num + 1) + ", Slot " + to_string(slot_num + 1) + "!";
    }
    string remove_car(int row_num, int slot_num)
    {
        if (row_num < 0 || row_num >= total_rows)
            return "ERROR: Row " + to_string(row_num + 1) + " does not exist!";
        if (slot[row_num] == nullptr || slot_num < 0 || slot_num >= slots_per_row[row_num])
            return "ERROR: Slot " + to_string(slot_num + 1) + " does not exist!";
        if (slot[row_num][slot_num] == "empty")
            return "ERROR: Slot is already empty!";

        string veh = slot[row_num][slot_num];
        slot[row_num][slot_num] = "empty";
        return "SUCCESS: " + veh + " removed from Row " +
            to_string(row_num + 1) + ", Slot " + to_string(slot_num + 1) + "!";
    }
    int* search_vehicle(string vehicle_num)
    {
        int* result = new int[2];
        for (int i = 0; i < total_rows; i++)
        {
            if (slot[i] == nullptr) continue;
            for (int j = 0; j < slots_per_row[i]; j++)
            {
                if (slot[i][j] == vehicle_num)
                {
                    result[0] = i;
                    result[1] = j;
                    return result;
                }
            }
        }
        delete[] result;
        return nullptr;
    }
    string empty_row(int row_num)
    {
        if (row_num < 0 || row_num >= total_rows)
            return "ERROR: Row " + to_string(row_num + 1) + " does not exist!";
        if (slot[row_num] == nullptr)
            return "ERROR: Row " + to_string(row_num + 1) + " has no slots yet!";

        for (int j = 0; j < slots_per_row[row_num]; j++)
            slot[row_num][j] = "empty";
        return "SUCCESS: Row " + to_string(row_num + 1) + " cleared!";
    }
    string resize_slots(int row_num, int new_size)
    {
        if (row_num < 0 || row_num >= total_rows)
            return "ERROR: Invalid row number!";
        if (new_size <= 0)
            return "ERROR: New size must be greater than 0!";

        if (new_size > slots_per_row[row_num])
        {
            string* temp = new string[new_size];
            for (int i = 0; i < slots_per_row[row_num]; i++) temp[i] = slot[row_num][i];
            for (int i = slots_per_row[row_num]; i < new_size; i++) temp[i] = "empty";
            delete[] slot[row_num];
            slot[row_num] = temp;
            slots_per_row[row_num] = new_size;
        }
        else
        {
            for (int i = new_size; i < slots_per_row[row_num]; i++)
            {
                if (slot[row_num][i] != "empty")
                    return "ERROR: Cannot shrink — slot " + to_string(i + 1) + " is occupied!";
            }
            string* temp = new string[new_size];
            for (int i = 0; i < new_size; i++) temp[i] = slot[row_num][i];
            delete[] slot[row_num];
            slot[row_num] = temp;
            slots_per_row[row_num] = new_size;
        }
        return "SUCCESS: Row " + to_string(row_num + 1) +
            " resized to " + to_string(new_size) + " slots!";
    }
    int    getTotalRows()              const { return total_rows; }
    int    getSlotsPerRow(int row)     const { return slots_per_row[row]; }
    string getSlot(int row, int col)   const { return slot[row][col]; }
    bool   rowHasSlots(int row)        const { return slot[row] != nullptr; }
};
const int WIN_W = 1280;
const int WIN_H = 800;
const int HEADER_H = 72;
const int STATUS_H = 46;
const int PANEL_W = 300;
const int PANEL_PAD = 12;

const float SLOT_W = 115.f;
const float SLOT_H = 68.f;
const float SLOT_GAP = 10.f;
const float ROW_GAP = 16.f;

const sf::Color C_BG_TOP(255, 228, 240);
const sf::Color C_BG_BOT(225, 215, 255);

const sf::Color C_HEADER(255, 188, 210);
const sf::Color C_HEADER_TXT(110, 55, 90);


const sf::Color C_PANEL(255, 245, 252, 230);
const sf::Color C_PANEL_BRD(220, 180, 215);


const sf::Color C_EMPTY(185, 242, 215);
const sf::Color C_OCCUPIED(255, 168, 168);
const sf::Color C_SELECTED(255, 220, 110);
const sf::Color C_SLOT_BRD(180, 155, 190);


const sf::Color C_BTN(210, 185, 255);
const sf::Color C_BTN_HOV(185, 150, 255);
const sf::Color C_BTN_TXT(75, 50, 115);


const sf::Color C_INPUT_BG(255, 255, 255);
const sf::Color C_INPUT_BRD(210, 175, 210);
const sf::Color C_INPUT_FOC(175, 110, 210);


const sf::Color C_STATUS_OK(210, 245, 228);
const sf::Color C_STATUS_ERR(255, 215, 220);
const sf::Color C_TXT_OK(35, 120, 75);
const sf::Color C_TXT_ERR(170, 35, 55);


const sf::Color C_TEXT(75, 55, 80);
const sf::Color C_TEXT_LIGHT(160, 130, 165);

void drawBackground(sf::RenderWindow& win)
{
    sf::VertexArray grad(sf::Quads, 4);
    grad[0] = { {0.f,       0.f      }, C_BG_TOP };
    grad[1] = { {(float)WIN_W, 0.f      }, C_BG_TOP };
    grad[2] = { {(float)WIN_W, (float)WIN_H}, C_BG_BOT };
    grad[3] = { {0.f,       (float)WIN_H}, C_BG_BOT };
    win.draw(grad);
}
void drawRoundedRect(sf::RenderWindow& win,
    float x, float y, float w, float h,
    float r,
    sf::Color fill, sf::Color border,
    float borderThick = 2.f)
{

    sf::RectangleShape hBar({ w - 2 * r, h });
    hBar.setPosition(x + r, y);
    hBar.setFillColor(fill);
    win.draw(hBar);


    sf::RectangleShape vBar({ w, h - 2 * r });
    vBar.setPosition(x, y + r);
    vBar.setFillColor(fill);
    win.draw(vBar);


    float cx[4] = { x + r,     x + w - r,   x + r,     x + w - r };
    float cy[4] = { y + r,     y + r,     y + h - r,   y + h - r };
    for (int i = 0; i < 4; i++)
    {
        sf::CircleShape c(r, 16);
        c.setOrigin(r, r);
        c.setPosition(cx[i], cy[i]);
        c.setFillColor(fill);
        win.draw(c);
    }


    sf::RectangleShape outline({ w, h });
    outline.setPosition(x, y);
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(border);
    outline.setOutlineThickness(borderThick);
    win.draw(outline);
}


void drawText(sf::RenderWindow& win, sf::Font& font,
    const string& str, float x, float y,
    unsigned size, sf::Color color,
    sf::Uint32 style = sf::Text::Regular)
{
    sf::Text t(str, font, size);
    t.setFillColor(color);
    t.setStyle(style);
    t.setPosition(x, y);
    win.draw(t);
}

void drawTextCentred(sf::RenderWindow& win, sf::Font& font,
    const string& str, sf::FloatRect box,
    unsigned size, sf::Color color,
    sf::Uint32 style = sf::Text::Regular)
{
    sf::Text t(str, font, size);
    t.setFillColor(color);
    t.setStyle(style);
    sf::FloatRect b = t.getLocalBounds();
    t.setPosition(box.left + (box.width - b.width) / 2.f - b.left,
        box.top + (box.height - b.height) / 2.f - b.top);
    win.draw(t);
}


void drawDiamond(sf::RenderWindow& win, float cx, float cy, float r, sf::Color col)
{
    sf::ConvexShape d(4);
    d.setPoint(0, { cx,   cy - r });
    d.setPoint(1, { cx + r, cy });
    d.setPoint(2, { cx,   cy + r });
    d.setPoint(3, { cx - r, cy });
    d.setFillColor(col);
    win.draw(d);
}

void drawHeart(sf::RenderWindow& win, float cx, float cy, float size, sf::Color col)
{
    float r = size * 0.28f;

    sf::CircleShape lc(r, 20), rc(r, 20);
    lc.setOrigin(r, r); lc.setPosition(cx - r * 0.7f, cy - r * 0.3f); lc.setFillColor(col);
    rc.setOrigin(r, r); rc.setPosition(cx + r * 0.7f, cy - r * 0.3f); rc.setFillColor(col);
    win.draw(lc);
    win.draw(rc);

    sf::ConvexShape tri(3);
    tri.setPoint(0, { cx - size * 0.55f, cy });
    tri.setPoint(1, { cx + size * 0.55f, cy });
    tri.setPoint(2, { cx,              cy + size * 0.6f });
    tri.setFillColor(col);
    win.draw(tri);
}

struct InputField
{
    sf::FloatRect rect;
    string        label;
    string        text;
    bool          focused;
    int           maxLen;

    InputField() : focused(false), maxLen(12) {}
    InputField(float x, float y, float w, float h,
        const string& lbl, int max = 12)
        : rect(x, y, w, h), label(lbl), focused(false), maxLen(max) {
    }

    bool contains(sf::Vector2f p) const { return rect.contains(p); }
    void handleChar(sf::Uint32 c)
    {
        if (!focused) return;
        if (c == 8)
        {
            if (!text.empty()) text.pop_back();
        }
        else if (c >= 32 && (int)text.size() < maxLen)
        {
            text += static_cast<char>(c);
        }
    }

    void draw(sf::RenderWindow& win, sf::Font& font) const
    {
        drawText(win, font, label, rect.left, rect.top - 19.f, 13, C_TEXT_LIGHT);
        sf::RectangleShape box({ rect.width, rect.height });
        box.setPosition(rect.left, rect.top);
        box.setFillColor(C_INPUT_BG);
        box.setOutlineColor(focused ? C_INPUT_FOC : C_INPUT_BRD);
        box.setOutlineThickness(2.f);
        win.draw(box);
        string display = text + (focused ? "|" : "");
        drawText(win, font, display, rect.left + 7.f, rect.top + 5.f, 15, C_TEXT);
    }
};

struct Button
{
    sf::FloatRect rect;
    string        label;
    bool          hovered;

    Button() : hovered(false) {}
    Button(float x, float y, float w, float h, const string& lbl)
        : rect(x, y, w, h), label(lbl), hovered(false) {
    }

    bool contains(sf::Vector2f p) const { return rect.contains(p); }

    void draw(sf::RenderWindow& win, sf::Font& font) const
    {
        sf::Color bg = hovered ? C_BTN_HOV : C_BTN;
        drawRoundedRect(win, rect.left, rect.top, rect.width, rect.height,
            10.f, bg, C_SLOT_BRD, 2.f);
        drawTextCentred(win, font, label, rect, 15, C_BTN_TXT, sf::Text::Bold);
    }
};
int main()
{
    parking_block pb(3);
    pb.add_slots(0, 5);
    pb.add_slots(1, 4);
    pb.add_slots(2, 6);
    pb.park_car(0, 0, "ABC-1234");
    pb.park_car(0, 3, "XYZ-9900");
    pb.park_car(1, 1, "LMN-4567");
    pb.park_car(2, 4, "QRS-0011");
    sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H),
        "Smart Parking System",
        sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
    sf::Font font;
    bool loaded = font.loadFromFile("C:/Users/Amraha/source/repos/study planner/study planner/x64/Release/Fonts/nunito.ttf");
    if (!loaded) loaded = font.loadFromFile("C:/Users/Amraha/source/repos/study planner/study planner/x64/Release/Fonts/nunito.ttf");
    if (!loaded) loaded = font.loadFromFile("C:/Users/Amraha/source/repos/study planner/study planner/x64/Release/Fonts/nunito.ttf");
    if (!loaded)
    {
        cout << "[ERROR] Could not load any font.\n"
            << "Please place a font.ttf in the same folder as this executable.\n"
            << "Tip: Download Nunito-Regular.ttf from fonts.google.com\n";
        return -1;
    }
    string statusMsg = "Welcome! Click a slot or use the panel on the right.";
    bool   statusOk = true;
    pair<int, int> selectedSlot = { -1, -1 };

    const float PX = WIN_W - PANEL_W - PANEL_PAD;
    const float PY = HEADER_H + PANEL_PAD;
    const float PH = WIN_H - HEADER_H - STATUS_H - PANEL_PAD * 2;
    const float IX = PX + 14.f;
    const float IW = PANEL_W - 28.f;

    float cy = PY + 36.f;

    InputField vehicleInput(IX, cy + 20.f, IW, 30.f, "Vehicle Number (e.g. ABC-1234):", 12);
    cy += 68.f;
    InputField rowInput(IX, cy + 20.f, IW / 2.f - 4.f, 30.f, "Row #:", 3);
    InputField slotInput(IX + IW / 2.f + 4.f, cy + 20.f, IW / 2.f - 4.f, 30.f, "Slot #:", 3);
    cy += 68.f;
    InputField sizeInput(IX, cy + 20.f, IW, 30.f, "New Size (for Resize Slots):", 3);
    cy += 68.f;

    const float BH = 38.f, BG = 8.f;
    Button btnPark(IX, cy, IW, BH, "Park Car");          cy += BH + BG;
    Button btnRemove(IX, cy, IW, BH, "Remove Car");        cy += BH + BG;
    Button btnSearch(IX, cy, IW, BH, "Search Vehicle");    cy += BH + BG;
    Button btnEmptyRow(IX, cy, IW, BH, "Empty Row");         cy += BH + BG;
    Button btnResize(IX, cy, IW, BH, "Resize Slots");

    vector<InputField*> inputs = { &vehicleInput, &rowInput, &slotInput, &sizeInput };
    vector<Button*>     buttons = { &btnPark, &btnRemove, &btnSearch, &btnEmptyRow, &btnResize };

    auto parseIdx = [](InputField& f) -> int {
        try { return stoi(f.text) - 1; }
        catch (...) { return -1; }
        };


    sf::Color heartCol(255, 120, 150, 210);
    sf::Color diamondCol(255, 200, 220, 180);

    while (window.isOpen())
    {
        sf::Vector2f mouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        for (auto* b : buttons) b->hovered = b->contains(mouse);
        sf::Event ev;
        while (window.pollEvent(ev))
        {

            if (ev.type == sf::Event::Closed) window.close();
            if (ev.type == sf::Event::TextEntered)
                for (auto* inp : inputs) inp->handleChar(ev.text.unicode);
            if (ev.type == sf::Event::MouseButtonPressed &&
                ev.mouseButton.button == sf::Mouse::Left)
            {
                for (auto* inp : inputs)
                    inp->focused = inp->contains(mouse);
                float gx = 15.f;
                float gy = (float)HEADER_H + 40.f;
                float curY = gy;
                for (int i = 0; i < pb.getTotalRows(); i++)
                {
                    if (pb.rowHasSlots(i))
                    {
                        float slotStartX = gx + 65.f;
                        for (int j = 0; j < pb.getSlotsPerRow(i); j++)
                        {
                            float sx = slotStartX + j * (SLOT_W + SLOT_GAP);
                            sf::FloatRect sr(sx, curY, SLOT_W, SLOT_H);
                            if (sr.contains(mouse))
                            {
                                selectedSlot = { i, j };
                                rowInput.text = to_string(i + 1);
                                slotInput.text = to_string(j + 1);
                            }
                        }
                    }
                    curY += SLOT_H + ROW_GAP;
                }
                if (btnPark.contains(mouse))
                {
                    string veh = vehicleInput.text;
                    if (veh.empty()) {
                        statusMsg = "Please enter a vehicle number first!";
                        statusOk = false;
                    }
                    else {
                        statusMsg = pb.park_car(parseIdx(rowInput),
                            parseIdx(slotInput), veh);
                        statusOk = (statusMsg.rfind("SUCCESS", 0) == 0);
                    }
                }

                if (btnRemove.contains(mouse))
                {
                    statusMsg = pb.remove_car(parseIdx(rowInput), parseIdx(slotInput));
                    statusOk = (statusMsg.rfind("SUCCESS", 0) == 0);
                    if (statusOk) selectedSlot = { -1, -1 };
                }

                if (btnSearch.contains(mouse))
                {
                    string veh = vehicleInput.text;
                    if (veh.empty()) {
                        statusMsg = "Please enter a vehicle number to search!";
                        statusOk = false;
                    }
                    else {
                        int* res = pb.search_vehicle(veh);
                        if (res) {
                            selectedSlot = { res[0], res[1] };
                            rowInput.text = to_string(res[0] + 1);
                            slotInput.text = to_string(res[1] + 1);
                            statusMsg = "SUCCESS: " + veh + " found at Row " +
                                to_string(res[0] + 1) + ", Slot " + to_string(res[1] + 1) + "!";
                            statusOk = true;
                            delete[] res;
                        }
                        else {
                            statusMsg = "ERROR: Vehicle \"" + veh + "\" not found!";
                            statusOk = false;
                        }
                    }
                }

                if (btnEmptyRow.contains(mouse))
                {
                    statusMsg = pb.empty_row(parseIdx(rowInput));
                    statusOk = (statusMsg.rfind("SUCCESS", 0) == 0);
                    if (statusOk) selectedSlot = { -1, -1 };
                }

                if (btnResize.contains(mouse))
                {
                    int newSz = -1;
                    try { newSz = stoi(sizeInput.text); }
                    catch (...) {}
                    if (newSz <= 0) {
                        statusMsg = "Please enter a valid new size!";
                        statusOk = false;
                    }
                    else {
                        statusMsg = pb.resize_slots(parseIdx(rowInput), newSz);
                        statusOk = (statusMsg.rfind("SUCCESS", 0) == 0);
                    }
                }
            }
        }
        window.clear();
        drawBackground(window);
        sf::RectangleShape header({ (float)WIN_W, (float)HEADER_H });
        header.setFillColor(C_HEADER);
        window.draw(header);
        drawHeart(window, 28, 22, 24, sf::Color(255, 90, 130, 200));
        drawHeart(window, 62, 28, 14, sf::Color(255, 140, 170, 180));
        drawHeart(window, WIN_W - 42, 22, 24, sf::Color(255, 90, 130, 200));
        drawHeart(window, WIN_W - 76, 28, 14, sf::Color(255, 140, 170, 180));
        for (int i = 0; i < 6; i++)
            drawDiamond(window, 100.f + i * 180.f, 15.f, 5.f, diamondCol);
        {
            string title = "~ Smart Parking System ~";
            sf::Text t(title, font, 30);
            t.setStyle(sf::Text::Bold);
            t.setFillColor(C_HEADER_TXT);
            sf::FloatRect tb = t.getLocalBounds();
            t.setPosition((WIN_W - tb.width) / 2.f - tb.left,
                (HEADER_H - tb.height) / 2.f - tb.top - 6.f);
            window.draw(t);
        }
        {
            string sub = "Park with love  *";
            sf::Text t(sub, font, 13);
            t.setFillColor(sf::Color(165, 85, 125));
            sf::FloatRect tb = t.getLocalBounds();
            t.setPosition((WIN_W - tb.width) / 2.f, HEADER_H - 20.f);
            window.draw(t);
        }
        drawRoundedRect(window, PX, PY, PANEL_W, PH, 14.f,
            C_PANEL, C_PANEL_BRD, 2.f);
        drawText(window, font, "* Controls *", PX + 14.f, PY + 10.f,
            16, sf::Color(140, 80, 150), sf::Text::Bold);
        drawHeart(window, PX + PANEL_W - 30.f, PY + 18.f, 14, sf::Color(220, 140, 180, 200));
        for (auto* inp : inputs) inp->draw(window, font);
        for (auto* btn : buttons) btn->draw(window, font);
        drawText(window, font, "Tip: click a slot to auto-fill row & slot",
            PX + 8.f, PY + PH - 22.f, 11, C_TEXT_LIGHT);
        float gx = 15.f;
        float gy = (float)HEADER_H + 12.f;
        float curY = gy;
        drawText(window, font, "* Parking Block *", gx, curY,
            16, sf::Color(130, 70, 130), sf::Text::Bold);

        float legendX = gx + 200.f, legendY = curY + 2.f;
        {
            sf::RectangleShape swatch({ 16.f, 16.f });
            swatch.setFillColor(C_EMPTY);
            swatch.setOutlineColor(C_SLOT_BRD); swatch.setOutlineThickness(1.f);
            swatch.setPosition(legendX, legendY);
            window.draw(swatch);
            drawText(window, font, "Empty", legendX + 20.f, legendY + 1.f, 12, C_TEXT);

            swatch.setFillColor(C_OCCUPIED);
            swatch.setPosition(legendX + 80.f, legendY);
            window.draw(swatch);
            drawText(window, font, "Occupied", legendX + 100.f, legendY + 1.f, 12, C_TEXT);

            swatch.setFillColor(C_SELECTED);
            swatch.setPosition(legendX + 190.f, legendY);
            window.draw(swatch);
            drawText(window, font, "Selected", legendX + 210.f, legendY + 1.f, 12, C_TEXT);
        }

        curY += 30.f;

        for (int i = 0; i < pb.getTotalRows(); i++)
        {
            string rowLabel = "Row " + to_string(i + 1);
            drawText(window, font, rowLabel,
                gx, curY + (SLOT_H - 14.f) / 2.f,
                13, C_TEXT, sf::Text::Bold);

            if (!pb.rowHasSlots(i))
            {
                drawText(window, font, "(no slots added)",
                    gx + 65.f, curY + 22.f, 12, C_TEXT_LIGHT);
                curY += SLOT_H + ROW_GAP;
                continue;
            }

            float slotStartX = gx + 65.f;
            for (int j = 0; j < pb.getSlotsPerRow(i); j++)
            {
                float sx = slotStartX + j * (SLOT_W + SLOT_GAP);
                string val = pb.getSlot(i, j);
                bool   isEmpty = (val == "empty");
                bool   isSel = (selectedSlot.first == i && selectedSlot.second == j);
                sf::Color cardColor = isEmpty ? C_EMPTY : C_OCCUPIED;
                if (isSel) cardColor = C_SELECTED;
                drawRoundedRect(window, sx, curY, SLOT_W, SLOT_H, 10.f,
                    cardColor, C_SLOT_BRD, isSel ? 3.f : 1.5f);
                drawText(window, font, "S" + to_string(j + 1),
                    sx + 5.f, curY + 4.f, 11, sf::Color(120, 90, 120));
                if (!isEmpty)
                    drawDiamond(window, sx + SLOT_W - 8.f, curY + 9.f, 5.f,
                        sf::Color(200, 60, 80, 200));
                string display = isEmpty ? "empty" : val;
                sf::Color txtCol = isEmpty ? sf::Color(45, 130, 90) : sf::Color(150, 35, 55);
                {
                    sf::Text t(display, font, 13);
                    t.setStyle(sf::Text::Bold);
                    t.setFillColor(txtCol);
                    sf::FloatRect b = t.getLocalBounds();
                    float tx = sx + (SLOT_W - min(b.width, SLOT_W - 10.f)) / 2.f;
                    t.setPosition(tx, curY + (SLOT_H - b.height) / 2.f + 4.f);
                    window.draw(t);
                }
            }

            curY += SLOT_H + ROW_GAP;
        }
        sf::RectangleShape statusBar({ (float)WIN_W, (float)STATUS_H });
        statusBar.setPosition(0.f, WIN_H - STATUS_H);
        statusBar.setFillColor(statusOk ? C_STATUS_OK : C_STATUS_ERR);
        window.draw(statusBar);
        sf::RectangleShape divider({ (float)WIN_W, 1.f });
        divider.setPosition(0.f, WIN_H - STATUS_H);
        divider.setFillColor(sf::Color(200, 170, 200, 180));
        window.draw(divider);
        string icon = statusOk ? "[OK] " : "[!]  ";
        drawText(window, font, icon + statusMsg,
            14.f, WIN_H - STATUS_H + 12.f,
            15, statusOk ? C_TXT_OK : C_TXT_ERR, sf::Text::Bold);

        window.display();
    }

    return 0;
}
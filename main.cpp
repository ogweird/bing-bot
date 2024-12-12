#include <Windows.h>
#include <thread>
#include <vector>

const std::string queries = "Cz�owiek od zawsze stara� si� zrozumie� otaczaj�cy go �wiat. Zanim nauka zyska�a swoje wsp�czesne formy, staro�ytne cywilizacje pr�bowa�y wyja�ni� zjawiska przyrodnicze za pomoc� mit�w i legend. W wielu kulturach istniej� opowie�ci o bogach, kt�rzy kieruj� losami ludzi, decyduj� o zmianach p�r roku, plonach czy pogodzie. Z biegiem czasu ludzka ciekawo�� zacz�a jednak prowadzi� do bardziej systematycznego badania natury. Prze�omowe odkrycia, takie jak teoria heliocentryczna Kopernika, dowody na istnienie mikroskopijnych organizm�w czy odkrycie grawitacji, zmienia�y spos�b, w jaki postrzegali�my nasz� planet� i wszech�wiat.Nasza percepcja rzeczywisto�ci jest nieustannie kszta�towana przez nauk� i technologi�.Dzi�, dzi�ki rozwoju technologii, mamy dost�p do informacji na niespotykan� wcze�niej skal�.Internet, sztuczna inteligencja, a tak�e nowoczesne narz�dzia umo�liwiaj� badanie wszech�wiata w spos�b, kt�ry jeszcze kilkadziesi�t lat temu wydawa�by si� niewyobra�alny.Z tego powodu jeste�my w stanie analizowa� dane, kt�re pozwalaj� na zrozumienie nie tylko naszej planety, ale tak�e innych galaktyk, a nawet pocz�tk�w �ycia.Jednak mimo tych wszystkich osi�gni��, wiele tajemnic pozostaje nadal nieodkrytych.Z jednej strony, post�p technologiczny daje nam ogromne mo�liwo�ci.Komputery o ogromnej mocy obliczeniowej, teleskopy zdolne do rejestrowania obraz�w odleg�ych gwiazd czy analiza danych genetycznych to tylko niekt�re z narz�dzi, kt�re otwieraj� przed nami nowe perspektywy.Z drugiej strony, w miar� jak technologia staje si� coraz bardziej zaawansowana, pojawiaj� si� tak�e pytania o jej wp�yw na nasze �ycie.Jakie konsekwencje mo�e mie� powszechne wykorzystywanie sztucznej inteligencji w pracy, edukacji czy nawet w �yciu codziennym ? Czy jeste�my w stanie zachowa� kontrol� nad technologi�, czy te� w pewnym momencie zacznie ona dominowa� nad nami ? To pytania, kt�re nie maj� jednoznacznych odpowiedzi, a na kt�re odpowiedzi wci�� poszukujemy.Nie mo�emy r�wnie� zapomina� o roli, jak� odgrywa �rodowisko w kontek�cie post�pu technologicznego.Z jednej strony, rozw�j przemys�u i technologii pozwoli� na popraw� jako�ci �ycia wielu ludzi, z drugiej jednak � przyczyni� si� do degradacji �rodowiska naturalnego.Wsp�czesne wyzwania zwi�zane z ochron� klimatu, zanieczyszczeniem powietrza i w�d stawiaj� przed nami pytanie, jak pogodzi� post�p z odpowiedzialno�ci� za przysz�e pokolenia.Wydaje si�, �e kluczowym wyzwaniem XXI wieku b�dzie znalezienie r�wnowagi pomi�dzy rozwojem a ochron� naszej planety.";

int random_range(int min, int max) noexcept {
    return min + (std::rand() % (max - min + 1));
}

std::string get_query() noexcept {
    int start_s = random_range(0, queries.size() / 2);

    return queries.substr(start_s, 30);
}

void start_search() noexcept {
    INPUT ctrl;
    ctrl.type = INPUT_KEYBOARD;
    ctrl.ki.wScan = 0;
    ctrl.ki.time = 0;
    ctrl.ki.dwExtraInfo = 0;
    ctrl.ki.wVk = 0x11;
    ctrl.ki.dwFlags = 0;

    INPUT k;
    k.type = INPUT_KEYBOARD;
    k.ki.wScan = 0;
    k.ki.time = 0;
    k.ki.dwExtraInfo = 0;
    k.ki.wVk = 0x4B;
    k.ki.dwFlags = 0;

    SendInput(1, &ctrl, sizeof(INPUT));

    k.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &k, sizeof(INPUT));

    ctrl.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ctrl, sizeof(INPUT));
}

void send_string_input(std::string query) noexcept {
    std::vector<INPUT> vec;

    for (auto c : query) {
        INPUT input = { 0 };

        input.type = INPUT_KEYBOARD;
        input.ki.dwFlags = KEYEVENTF_UNICODE;
        input.ki.wScan = c;

        vec.push_back(input);

        input.ki.dwFlags = KEYEVENTF_KEYUP;
        vec.push_back(input);
    }

    SendInput(vec.size(), vec.data(), sizeof(INPUT));
}

void press_enter(int delay_s) noexcept {
    INPUT enter;
    enter.type = INPUT_KEYBOARD;
    enter.ki.wScan = 0;
    enter.ki.time = 0;
    enter.ki.dwExtraInfo = 0;
    enter.ki.wVk = 0x0D;
    enter.ki.dwFlags = 0;

    std::this_thread::sleep_for(std::chrono::seconds(delay_s));

    SendInput(1, &enter, sizeof(INPUT));
    enter.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &enter, sizeof(INPUT));
}

void main_thread() {
    start_search();
    send_string_input(get_query());
    press_enter(2);

    std::this_thread::sleep_for(std::chrono::seconds(10));
}

int main(void) {
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::thread core(main_thread);

    while (!GetAsyncKeyState(VK_END)) {
        continue;
    }

    core.~thread();
}
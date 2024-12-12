#include <Windows.h>
#include <thread>
#include <vector>

const std::string queries = "Cz³owiek od zawsze stara³ siê zrozumieæ otaczaj¹cy go œwiat. Zanim nauka zyska³a swoje wspó³czesne formy, staro¿ytne cywilizacje próbowa³y wyjaœniæ zjawiska przyrodnicze za pomoc¹ mitów i legend. W wielu kulturach istniej¹ opowieœci o bogach, którzy kieruj¹ losami ludzi, decyduj¹ o zmianach pór roku, plonach czy pogodzie. Z biegiem czasu ludzka ciekawoœæ zaczê³a jednak prowadziæ do bardziej systematycznego badania natury. Prze³omowe odkrycia, takie jak teoria heliocentryczna Kopernika, dowody na istnienie mikroskopijnych organizmów czy odkrycie grawitacji, zmienia³y sposób, w jaki postrzegaliœmy nasz¹ planetê i wszechœwiat.Nasza percepcja rzeczywistoœci jest nieustannie kszta³towana przez naukê i technologiê.Dziœ, dziêki rozwoju technologii, mamy dostêp do informacji na niespotykan¹ wczeœniej skalê.Internet, sztuczna inteligencja, a tak¿e nowoczesne narzêdzia umo¿liwiaj¹ badanie wszechœwiata w sposób, który jeszcze kilkadziesi¹t lat temu wydawa³by siê niewyobra¿alny.Z tego powodu jesteœmy w stanie analizowaæ dane, które pozwalaj¹ na zrozumienie nie tylko naszej planety, ale tak¿e innych galaktyk, a nawet pocz¹tków ¿ycia.Jednak mimo tych wszystkich osi¹gniêæ, wiele tajemnic pozostaje nadal nieodkrytych.Z jednej strony, postêp technologiczny daje nam ogromne mo¿liwoœci.Komputery o ogromnej mocy obliczeniowej, teleskopy zdolne do rejestrowania obrazów odleg³ych gwiazd czy analiza danych genetycznych to tylko niektóre z narzêdzi, które otwieraj¹ przed nami nowe perspektywy.Z drugiej strony, w miarê jak technologia staje siê coraz bardziej zaawansowana, pojawiaj¹ siê tak¿e pytania o jej wp³yw na nasze ¿ycie.Jakie konsekwencje mo¿e mieæ powszechne wykorzystywanie sztucznej inteligencji w pracy, edukacji czy nawet w ¿yciu codziennym ? Czy jesteœmy w stanie zachowaæ kontrolê nad technologi¹, czy te¿ w pewnym momencie zacznie ona dominowaæ nad nami ? To pytania, które nie maj¹ jednoznacznych odpowiedzi, a na które odpowiedzi wci¹¿ poszukujemy.Nie mo¿emy równie¿ zapominaæ o roli, jak¹ odgrywa œrodowisko w kontekœcie postêpu technologicznego.Z jednej strony, rozwój przemys³u i technologii pozwoli³ na poprawê jakoœci ¿ycia wielu ludzi, z drugiej jednak – przyczyni³ siê do degradacji œrodowiska naturalnego.Wspó³czesne wyzwania zwi¹zane z ochron¹ klimatu, zanieczyszczeniem powietrza i wód stawiaj¹ przed nami pytanie, jak pogodziæ postêp z odpowiedzialnoœci¹ za przysz³e pokolenia.Wydaje siê, ¿e kluczowym wyzwaniem XXI wieku bêdzie znalezienie równowagi pomiêdzy rozwojem a ochron¹ naszej planety.";

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
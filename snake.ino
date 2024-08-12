#include <Adafruit_NeoPixel.h>
#include "deque.h"

#define BUTTON_N 4
#define BUTTON_S 7
#define BUTTON_E 8
#define BUTTON_W 2


#define NUM_LEDS 256
#define DATA_PIN 10
#define MATRIX_WIDTH 16
#define MATRIX_HEIGHT 16

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

int matrix[16][16][2] = {
  {{15, 0}, {14, 0}, {13, 0}, {12, 0}, {11, 0}, {10, 0}, {9, 0}, {8, 0}, {7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
  {{16, 0}, {17, 0}, {18, 0}, {19, 0}, {20, 0}, {21, 0}, {22, 0}, {23, 0}, {24, 0}, {25, 0}, {26, 0}, {27, 0}, {28, 0}, {29, 0}, {30, 0}, {31, 0}},
  {{47, 0}, {46, 0}, {45, 0}, {44, 0}, {43, 0}, {42, 0}, {41, 0}, {40, 0}, {39, 0}, {38, 0}, {37, 0}, {36, 0}, {35, 0}, {34, 0}, {33, 0}, {32, 0}},
  {{48, 0}, {49, 0}, {50, 0}, {51, 0}, {52, 0}, {53, 0}, {54, 0}, {55, 0}, {56, 0}, {57, 0}, {58, 0}, {59, 0}, {60, 0}, {61, 0}, {62, 0}, {63, 0}},
  {{79, 0}, {78, 0}, {77, 0}, {76, 0}, {75, 0}, {74, 0}, {73, 0}, {72, 0}, {71, 0}, {70, 0}, {69, 0}, {68, 0}, {67, 0}, {66, 0}, {65, 0}, {64, 0}},
  {{80, 0}, {81, 0}, {82, 0}, {83, 0}, {84, 0}, {85, 0}, {86, 0}, {87, 0}, {88, 0}, {89, 0}, {90, 0}, {91, 0}, {92, 0}, {93, 0}, {94, 0}, {95, 0}},
  {{111, 0}, {110, 0}, {109, 0}, {108, 0}, {107, 0}, {106, 0}, {105, 0}, {104, 0}, {103, 0}, {102, 0}, {101, 0}, {100, 0}, {99, 0}, {98, 0}, {97, 0}, {96, 0}},
  {{112, 0}, {113, 0}, {114, 0}, {115, 0}, {116, 0}, {117, 0}, {118, 0}, {119, 0}, {120, 0}, {121, 0}, {122, 0}, {123, 0}, {124, 0}, {125, 0}, {126, 0}, {127, 0}},
  {{143, 0}, {142, 0}, {141, 0}, {140, 0}, {139, 0}, {138, 0}, {137, 0}, {136, 0}, {135, 0}, {134, 0}, {133, 0}, {132, 0}, {131, 0}, {130, 0}, {129, 0}, {128, 0}},
  {{144, 0}, {145, 0}, {146, 0}, {147, 0}, {148, 0}, {149, 0}, {150, 0}, {151, 0}, {152, 0}, {153, 0}, {154, 0}, {155, 0}, {156, 0}, {157, 0}, {158, 0}, {159, 0}},
  {{175, 0}, {174, 0}, {173, 0}, {172, 0}, {171, 0}, {170, 0}, {169, 11}, {168, 0}, {167, 0}, {166, 0}, {165, 0}, {164, 0}, {163, 0}, {162, 0}, {161, 0}, {160, 0}},
  {{176, 0}, {177, 0}, {178, 0}, {179, 0}, {180, 0}, {181, 0}, {182, 0}, {183, 0}, {184, 0}, {185, 0}, {186, 0}, {187, 0}, {188, 0}, {189, 0}, {190, 0}, {191, 0}},
  {{207, 0}, {206, 0}, {205, 0}, {204, 0}, {203, 0}, {202, 0}, {201, 0}, {200, 0}, {199, 0}, {198, 0}, {197, 0}, {196, 0}, {195, 0}, {194, 0}, {193, 0}, {192, 0}},
  {{208, 0}, {209, 0}, {210, 0}, {211, 0}, {212, 0}, {213, 0}, {214, 0}, {215, 0}, {216, 0}, {217, 0}, {218, 0}, {219, 0}, {220, 0}, {221, 0}, {222, 0}, {223, 0}},
  {{239, 0}, {238, 0}, {237, 0}, {236, 0}, {235, 0}, {234, 0}, {233, 0}, {232, 0}, {231, 0}, {230, 0}, {229, 0}, {228, 0}, {227, 0}, {226, 0}, {225, 0}, {224, 0}},
  {{240, 0}, {241, 0}, {242, 0}, {243, 0}, {244, 0}, {245, 0}, {246, 0}, {247, 0}, {248, 0}, {249, 0}, {250, 0}, {251, 0}, {252, 0}, {253, 0}, {254, 0}, {255, 0}},
};

int head[2] = {6, 10};
int score = 0;
Deque<int> snake(90);

void error(void)
{
  strip.setPixelColor(0, strip.Color(255, 0, 0));
  strip.show();
  delay(1000);
  exit(1);
}


void change_led_state(int x, int y, int R, int G, int B)
{
  if (matrix[y][x][1] == 1)
  {
    error();
  }
  strip.setPixelColor(matrix[y][x][0], strip.Color(R, G, B));
  matrix[y][x][1] = R;
}


void make_new_fruit(void)
{
  long r = random(0, 256 - score);
  long count = 0;

  for (int y = 0; y < 16; y++)
  {
    for (int x = 0; x < 16; x++)
      if (matrix[y][x][1] == 0)
      {
        if (count == r)
        {
          change_led_state(x, y, 15, 0, 0);
          return;
        }
        count++;
      }
  }
}


void check_led(int x, int y)
{
  if (x > 15 || x < 0 || y > 15 || y < 0)
    error();

  int red_val = matrix[y][x][1];

  if (red_val == 11)
  {
    strip.setPixelColor(15, strip.Color(255, 0, 0));
    strip.show();
    delay(1000);
    exit(1);
  }
  else if (red_val == 15)
  {
    score++;
    make_new_fruit();
  }
  else if (red_val == 0)
  {
    strip.setPixelColor(snake.back(), strip.Color(0, 0, 0));
    snake.pop_back();
  }
  change_led_state(x, y, 11, 11, 11);
  strip.show();
}


char read_pins(char prev)
{
  if (digitalRead(BUTTON_E) == HIGH)
    return 'E';
  if (digitalRead(BUTTON_W) == HIGH)
    return 'W';
  if (digitalRead(BUTTON_N) == HIGH)
    return 'N';
  if (digitalRead(BUTTON_S) == HIGH)
    return 'S';
  else
    return prev;
}


void move(void)
{
  static char dir = 'N';

  dir = read_pins(dir);

  switch (dir)
  {
    case 'N':
      head[1] = head[1] - 1;
      check_led(head[0], head[1]);
      break;
    case 'S':
      head[1] = head[1] + 1;
      check_led(head[0], head[1]);
      break;
    case 'E':
      head[0] = head[0] + 1;
      check_led(head[0], head[1]);
      break;
    case 'W':
      head[0] = head[0] - 1;
      check_led(head[0], head[1]);
      break;

    default:
      error();
  }
}

void setup() {
  snake.push_front(matrix[head[1]][head[0]][0]);
  strip.begin();
  strip.setPixelColor(169, strip.Color(11, 11, 11));
  strip.show();
  pinMode(BUTTON_E, INPUT);
  pinMode(BUTTON_W, INPUT);
  pinMode(BUTTON_N, INPUT);
  pinMode(BUTTON_S, INPUT);
}

void loop() {
  move();
  delay(200);
}

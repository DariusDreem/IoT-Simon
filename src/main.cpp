#include <Arduino.h>

int ledPin[4] = {12, 13, 14, 15};
int buttonPin[4] = {32, 22, 23, 33};

const int tailleListe = 10;
int maListe[tailleListe];

int GetPin()
// Récupère le bouton qui va être appuyé en les testant tous a la chaine jusqu'a ce qu'un soit appuyé
{
  while (true)
  {
    // Boucle jusqu'a ce qu'un bouton soit appuyé
    for (int i = 0; i < 4; i++)
    {
      // Teste chaque bouton
      if (digitalRead(buttonPin[i]) == LOW)
      // Si le bouton est appuyé, on retourne son index
      {
        Serial.println(digitalRead(buttonPin[i]));
        return i;
      }
    }
  }
}

void ShowLed(int index)
// Allume les leds dans l'ordre de la liste
{
  for (int i = 0; i < index; i++)
  {
    // Allume les leds dans l'ordre de la liste
    digitalWrite(ledPin[maListe[i]], HIGH);
    delay(1000);
    digitalWrite(ledPin[maListe[i]], LOW);
    delay(300);
  }
}

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(A0));

  for (int i = 0; i < 4; i++)
  {
    // Initialisation des pins
    pinMode(ledPin[i], OUTPUT);
    pinMode(buttonPin[i], INPUT_PULLUP);
  }
}

void loop()
{
  int playerList[10];

  for (int index = 0; index < tailleListe; index++)
  {
    int newColor = random(4); // Génère un nombre aléatoire
    Serial.println(newColor);
    Serial.println(ledPin[newColor]);
    maListe[index] = newColor; // Ajoute le nombre a la liste

    ShowLed(index); // Allume les leds dans l'ordre de la liste

    for (int i = 0; i <= index; i++)
    {
      // Récupère le ou les boutons appuyés par le joueur
      playerList[i] = GetPin(); // Récupère le bouton appuyé
      Serial.println("in player list : " + String(playerList[i]) + " in maListe : " + String(maListe[i]));
    }

    for (int i = 0; i <= index; i++)
    {
      // Vérifie si la liste du joueur est identique a la liste générée
      if (maListe[i] != playerList[i])
      {
        // Si la liste est différente, le joueur a perdu
        Serial.println("Perdu !");
        return;
      }
    }
  }
}
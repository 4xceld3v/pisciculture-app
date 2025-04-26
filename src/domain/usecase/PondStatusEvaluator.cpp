#include "PondStatusEvaluator.h"

String PondStatusEvaluator::evaluateStatus(const Pond& data) {
    
    Serial.println(String("Temperature: ") + String(data.getTemperature()));
    Serial.println(String("Ph: ") + String(data.getPH()));

    bool tempFria = data.getTemperature() < 22;
    bool tempIdeal = data.getTemperature() >= 22 && data.getTemperature() <= 30;
    bool tempCaliente = data.getTemperature() > 30;

    bool phAcido = data.getPH() < 6.5;
    bool phNeutro = data.getPH() >= 6.5 && data.getPH() <= 8.5;
    bool phAlcalino = data.getPH() > 8.5;

   if (tempCaliente && phAlcalino) {
        return "ALERTA";
    } else if (phNeutro && tempIdeal){
        return "ESTABLE";
    }else {
        return "ACEPTABLE";
    }

 /*// Clasificación difusa aproximada

  // --- Temperatura ---
  bool tempFria = temp < 22;
  bool tempIdeal = temp >= 22 && temp <= 30;
  bool tempCaliente = temp > 30;

  // --- pH ---
  bool phAcido = ph < 6.5;
  bool phNeutro = ph >= 6.5 && ph <= 8.5;
  bool phAlcalino = ph > 8.5;

  // --- Oxígeno ---
  bool oxiBajo = oxi < 5;
  bool oxiAdecuado = oxi >= 5 && oxi <= 8;
  bool oxiAlto = oxi > 8;

  // --- Turbidez ---
  bool turbAlta = turb > 100;
  bool turbModerada = turb > 50 && turb <= 100;
  bool turbClara = turb <= 50;

  // --- Reglas de Inferencia ---

  if (tempFria && oxiBajo) return "CRITICO";                     // R1
  if (phAcido && turbAlta) return "CRITICO";                     // R2
  if (tempIdeal && oxiAdecuado && phNeutro) return "ESTABLE";   // R3
  if (turbAlta || oxiBajo) return "ALERTA";                     // R4
  if (tempCaliente && phAlcalino) return "ALERTA";              // R5
  if (turbModerada && oxiAdecuado) return "ACEPTABLE";          // R6
  if (phNeutro && tempIdeal) return "ESTABLE";                  // R7
  if (oxiAlto) return "RIESGO: SUPERSATURACION";                 // R8
  if (oxiBajo && phAcido) return "CRITICO";                     // R9

  return "SIN DEFINIR";
  */
}

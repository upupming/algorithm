/**
 * @param {number} initialEnergy
 * @param {number} initialExperience
 * @param {number[]} energy
 * @param {number[]} experience
 * @return {number}
 */
const minNumberOfHours = function (initialEnergy, initialExperience, energy, experience) {
  let tg = 0; let te = initialExperience
  let se = 0

  for (const a of energy) tg += a
  tg += 1
  tg = Math.max(tg, initialEnergy)

  for (let i = 0; i < experience.length; i++) {
    te = Math.max(te, experience[i] - se + 1)
    se += experience[i]
  }

  return tg - initialEnergy + te - initialExperience
}

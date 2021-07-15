import Annoy, { Metric } from "../dist";

const annoy = new Annoy(128, Metric.ANGULAR);

for (let i = 0; i < 1000; i += 1) {
  const vector = new Float64Array(128);
  for (let v = 0; v < 128; v += 1) {
    vector[v] = Math.random();
  }

  annoy.addItem(i, vector);
}

annoy.build(10);

const result = annoy.get_nns_by_item(0, 2, true);
annoy.save("a.ann");
console.log(result);

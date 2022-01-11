const addon = require("bindings")("annoy-node.node");

export enum Metric {
  ANGULAR = 1,
  EUCLIDEAN,
  MANHATTAN,
  DOTPRODUCT,
}
export interface AnnoyIndex {
  new (vectorSize: number, metric: Metric): AnnoyIndex;
  /**
   * 
   * @param item interger number
   * @param data Float64Array to be added in annoy index
   */
  addItem(item: Number, data: Float32Array): void;
  build(treeSize: Number, threads?: Number): void;
  save(path: string): void;
  load(path: string): void;
  unload(): void;
  get_nns_by_item(
    item: Number,
    n: Number,
    includeDistances: boolean
  ): { neighbours: Array<Int32Array>; distances?: Array<Int32Array> };
  get_nns_by_vector(
    item: Float32Array,
    n: Number,
    includeDistances: boolean
  ): { neighbours: Array<Int32Array>; distances?: Array<Int32Array> };
}

const annoy: AnnoyIndex = addon.AnnoyIndex;

export default annoy;

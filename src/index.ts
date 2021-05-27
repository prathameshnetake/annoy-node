const addon = require("../build/Release/annoy-node.node");

export interface AnnoyIndex {
  addItem(item: Number, data: Float64Array): void;
}

export const AnnoyIndex: {
  new (vectorSize: number, treeSize: number): AnnoyIndex;
} = addon.AnnoyIndex;

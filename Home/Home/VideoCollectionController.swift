//
//  VideoCollectionController.swift
//  Home
//
//  Created by miaokii on 2020/5/8.
//  Copyright © 2020 ly. All rights reserved.
//

import UIKit
import SnapKit

class VideoCollectionController: UIViewController {
    
    private let CellIdentifier = "CellIdentifier"
    
    var collectionView: UICollectionView!
    
    init() {
        
        let flowLayout = UICollectionViewFlowLayout.init()
        flowLayout.minimumLineSpacing = 1
        flowLayout.minimumInteritemSpacing = 1
        
        let width = (UIScreen.main.bounds.width - 2) / 2
        flowLayout.itemSize = CGSize.init(width: width, height: width)
        collectionView = UICollectionView.init(frame: .zero, collectionViewLayout: flowLayout)
        super.init(nibName: nil, bundle: nil)
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        view.backgroundColor = .white
        collectionView.backgroundColor = .background
        collectionView.dataSource = self
        collectionView.showsVerticalScrollIndicator = false
        collectionView.register(UICollectionViewCell.classForCoder(), forCellWithReuseIdentifier: CellIdentifier)
        view.addSubview(collectionView)
        collectionView.snp.makeConstraints { (make) in
            make.top.left.right.equalToSuperview()
            make.bottom.equalTo(view.safeAreaLayoutGuide.snp.bottom)
        }
        
    }
}

extension VideoCollectionController: UICollectionViewDataSource, UICollectionViewDelegateFlowLayout {
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return 20
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: CellIdentifier, for: indexPath)
        cell.backgroundColor = .systemRed
        return cell
    }
    
//    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, sizeForItemAt indexPath: IndexPath) -> CGSize {
//    }
}

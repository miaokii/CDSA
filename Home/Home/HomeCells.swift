//
//  File.swift
//  Home
//
//  Created by miaokii on 2020/5/7.
//  Copyright © 2020 ly. All rights reserved.
//

import Foundation
import UIKit
import SnapKit

extension UICollectionReusableView {
    static var reuseID: String {
        return NSStringFromClass(self.classForCoder())
    }
}

extension UITableViewCell {
    static var reuseID: String {
        return NSStringFromClass(self.classForCoder())
    }
}

class PageHomeCell: UITableViewCell {
    
    private var containerView = UIView()
    private var pageTitleLabel = UILabel.init()
    
    var contentScrollViews = [UIScrollView]()
    var pageScrollDidSwitchClosure:((UIScrollView)->Void)?
    var pageScrollView = UIScrollView.init()
    var currentScrollView: UIScrollView {
        if pageScrollView.frame == .zero {
            return contentScrollViews[0]
        }
        let index = Int(pageScrollView.contentOffset.x / pageScrollView.frame.size.width)
        return contentScrollViews[index]
    }
    
    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        
        contentView.backgroundColor = .background
        selectionStyle = .none
        contentView.addSubview(containerView)
        containerView.backgroundColor = .viewBackgroundColorLevel1
        containerView.layer.cornerRadius = 5
        containerView.clipsToBounds = true
        containerView.snp.makeConstraints { (make) in
            make.top.left.equalTo(10)
            make.right.equalTo(-10)
            make.bottom.equalToSuperview()
        }
        
        pageTitleLabel.textAlignment = .center
        pageTitleLabel.text = "我是 分页标题栏"
        containerView.addSubview(pageTitleLabel)
        pageTitleLabel.snp.makeConstraints { (make) in
            make.top.left.right.equalToSuperview()
            make.height.equalTo(44).priority(.required)
        }
        
        pageScrollView.isPagingEnabled = true
        pageScrollView.delegate = self
        pageScrollView.bounces = false
        containerView.addSubview(pageScrollView)
        pageScrollView.snp.makeConstraints { (make) in
            make.left.right.equalToSuperview()
            make.top.equalTo(pageTitleLabel.snp.bottom)
            make.bottom.equalToSuperview()
        }
//        pageScrollView.contentSize = .init(width: 0, height: 0)
        addSubCollection()
    }
    
    var pageCount: Int = 5 {
        didSet {
            pageScrollView.subviews.forEach { (sub) in
                sub.removeFromSuperview()
            }
            contentScrollViews.removeAll()
            addSubCollection()
            
            pageTitleLabel.text = "共有\(pageCount)页，当前在第\(pageCount)页"
        }
    }
    
    private func addSubCollection() {
        let flowLayout = UICollectionViewFlowLayout.init()
        flowLayout.minimumLineSpacing = 2
        flowLayout.minimumInteritemSpacing = 2
        flowLayout.scrollDirection = .vertical
        for i in 0..<pageCount {
            let collectionView = UICollectionView.init(frame: .zero, collectionViewLayout: flowLayout)
            collectionView.backgroundColor = .background
            collectionView.tag = i * 10 + 1
            collectionView.bounces = false
            collectionView.delegate = self
            collectionView.dataSource = self
            collectionView.isScrollEnabled = false
            collectionView.showsVerticalScrollIndicator = false
            collectionView.showsHorizontalScrollIndicator = false
            pageScrollView.addSubview(collectionView)
            collectionView.register(CollectionCell.classForCoder(), forCellWithReuseIdentifier: CollectionCell.reuseID)
            collectionView.snp.makeConstraints { (make) in
                make.left.equalTo(CGFloat(i) * (UIScreen.main.bounds.size.width - 20))
                make.top.equalToSuperview()
                make.width.equalToSuperview()
                make.height.equalTo(UIScreen.main.bounds.size.height)
            }
            contentScrollViews.append(collectionView)
        }

        pageScrollView.contentSize = .init(width: CGFloat(pageCount) * (UIScreen.main.bounds.size.width - 20), height: 0)
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
    }
}

extension PageHomeCell: UIScrollViewDelegate {
    func scrollViewDidEndDecelerating(_ scrollView: UIScrollView) {
        pageScrollDidSwitchClosure?(currentScrollView)
    }
}

extension PageHomeCell: UICollectionViewDelegate, UICollectionViewDataSource, UICollectionViewDelegateFlowLayout {
    
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return 10
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: CollectionCell.reuseID, for: indexPath)
        return cell
    }
    
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, sizeForItemAt indexPath: IndexPath) -> CGSize {
        let itemWidth = (collectionView.frame.size.width - 2) / 2
        return CGSize.init(width: itemWidth, height: itemWidth)
    }
}

class CollectionCell: UICollectionViewCell {
    override init(frame: CGRect) {
        super.init(frame: frame)
        backgroundColor = .niceRed
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
    }
}

class NormalHomeCell: UITableViewCell {
    
    private var containerView = UIView()
    
    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        contentView.backgroundColor = .background
        selectionStyle = .none
        contentView.addSubview(containerView)
        containerView.backgroundColor = .viewBackgroundColorLevel1
        containerView.layer.cornerRadius = 5
        containerView.clipsToBounds = true
        containerView.snp.makeConstraints { (make) in
            make.top.left.equalTo(10)
            make.right.equalTo(-10)
            make.bottom.equalToSuperview()
            make.height.equalTo(100).priority(.required)
        }
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
    }
}

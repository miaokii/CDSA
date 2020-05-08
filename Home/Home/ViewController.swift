//
//  ViewController.swift
//  Home
//
//  Created by miaokii on 2020/5/7.
//  Copyright © 2020 ly. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    private var mainScrollview = UIScrollView()
    private var mainTableView = UITableView()
    private var pageCell: PageHomeCell = PageHomeCell()
    private var pageHeight: CGFloat = 0
    private var currentScrollView: UIScrollView! {
        didSet {
            guard oldValue != currentScrollView else {
                return
            }
            if oldValue != nil {
                oldValue.removeObserver(self, forKeyPath: "contentSize")
            }
            currentScrollView.addObserver(self, forKeyPath: "contentSize", options: [.new,.old], context: nil)
            reloadPageCell()
        }
    }
    
    var pageCount: Int = 5
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        view.isUserInteractionEnabled = true
        view.addSubview(mainScrollview)
        view.addSubview(mainTableView)
        
        mainScrollview.snp.makeConstraints { (make) in
            make.top.left.right.equalToSuperview()
            make.bottom.equalTo(view.safeAreaLayoutGuide.snp.bottom)
        }
        
        mainTableView.snp.makeConstraints { (make) in
            make.top.left.bottom.right.equalTo(mainScrollview)
        }
        
        pageCell.pageScrollDidSwitchClosure = { [unowned self] (scrollView) in
            self.pageSwithTo(scrollView: scrollView)
        }
        
        mainScrollview.mj_header = MJDyRefresh.init(refreshingBlock: { [unowned self] in
            self.request(first: true)
        })

        mainScrollview.mj_footer = MJDyFooter.init(refreshingBlock: { [unowned self] in
            self.request(first: false)
        })
        
        mainScrollview.isScrollEnabled = true
        mainScrollview.backgroundColor = .background
        mainScrollview.bounces = true
        mainScrollview.delegate = self
        view.addGestureRecognizer(mainScrollview.panGestureRecognizer)
        mainScrollview.contentInsetAdjustmentBehavior = .never
        
        mainTableView.tableFooterView = UIView()
        mainTableView.backgroundColor = UIColor.background
        mainTableView.separatorStyle = .none
        mainTableView.isScrollEnabled = false
        mainTableView.delegate = self
        mainTableView.dataSource = self
        mainTableView.contentInsetAdjustmentBehavior = .never
        mainTableView.register(NormalHomeCell.classForCoder(), forCellReuseIdentifier: NormalHomeCell.reuseID)
        mainTableView.register(PageHomeCell.classForCoder(), forCellReuseIdentifier: PageHomeCell.reuseID)

        mainTableView.addObserver(self, forKeyPath: "contentSize", options: .new, context: nil)
        currentScrollView = pageCell.currentScrollView
    }
}

extension ViewController {
    private func request(first: Bool) {
        if first {
            DispatchQueue.main.asyncAfter(deadline: .now() + 1) {
                
                if first {
                    self.pageCount = Int(arc4random()%6 + 1)
                    let indexPath = IndexPath.init(row: 0, section: 1)
                    self.mainTableView.reloadRows(at: [indexPath], with: .none)
                }
                
                self.endRefresh()
            }
        }
        
    }
    
    private func endRefresh() {
        mainScrollview.mj_footer?.endRefreshing()
        mainScrollview.mj_header?.endRefreshing()
    }
}

extension ViewController {
    override func observeValue(forKeyPath keyPath: String?, of object: Any?, change: [NSKeyValueChangeKey : Any]?, context: UnsafeMutableRawPointer?) {
        guard keyPath == "contentSize", let conObject = object as? UIScrollView else {
            return
        }

        if conObject == mainTableView {
            let offset = mainScrollview.contentOffset
            mainScrollview.contentSize = mainTableView.contentSize
            mainScrollview.setContentOffset(offset, animated: false)
        } else if conObject == currentScrollView {
            guard let changeDic = change, let old = changeDic[NSKeyValueChangeKey(rawValue: "old")] as? CGSize, let new = changeDic[NSKeyValueChangeKey(rawValue: "new")] as? CGSize else {
                reloadPageCell()
                return
            }

            guard new != old else {
                return
            }
            reloadPageCell()
        }
    }
    
    private func reloadPageCell() {
        pageHeight = currentScrollView.contentSize.height + 44
        mainTableView.reloadData()
    }
    
    private func minPageSectionY() -> CGFloat {
        guard let cell = mainTableView.cellForRow(at: IndexPath.init(row: 0, section: 1)) else {
            return 0
        }
        return cell.frame.minY
    }
    
    private func pageSwithTo(scrollView: UIScrollView) {
        let miny = minPageSectionY()
        if mainScrollview.contentOffset.y >= miny {
            let offsetY = scrollView.contentOffset.y + miny
            mainScrollview.contentOffset = .init(x: 0, y: offsetY)
        }
        currentScrollView = scrollView
    }
}

extension ViewController: UICollectionViewDelegate {
    func scrollViewDidScroll(_ scrollView: UIScrollView) {
        if scrollView == mainScrollview {
            let offSety = scrollView.contentOffset.y
            let minY = minPageSectionY()
            if offSety >= minY {
                mainTableView.contentOffset = .init(x: 0, y: minY)
                currentScrollView.contentOffset = CGPoint.init(x: 0, y: offSety - minY)
            } else {
                mainTableView.contentOffset = mainScrollview.contentOffset
                pageCell.currentScrollView.contentOffset = .zero
            }
        }
    }
    
    func scrollViewWillBeginDragging(_ scrollView: UIScrollView) {
        for scroll in pageCell.contentScrollViews {
            if scroll != currentScrollView {
                scroll.contentOffset = .zero
            }
        }
    }
}

extension ViewController: UITableViewDelegate, UITableViewDataSource {
    func numberOfSections(in tableView: UITableView) -> Int {
        return 2
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if section == 0 {
            return 4
        }
        return 1
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        if indexPath.section == 0 {
            let cell = tableView.dequeueReusableCell(withIdentifier: NormalHomeCell.reuseID, for: indexPath) as! NormalHomeCell
            return cell
        } else {
//            pageCell.pageCount = pageCount
            return pageCell
        }
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        if indexPath.section == 0 {
            return tableView.estimatedRowHeight
        } else {
            return pageHeight
        }
    }
}

